#include "gameboard.h"
#include <random>

//I think these arent const
//const std::vector<GameBoard::CritFunction> GameBoard::SettlementCriteria = 
//{
//    //probaljuk ki & nelkul vicces
//    &GameBoard::Crit_isFreeNode,&GameBoard::Crit_Distance,&GameBoard::Crit_Node_Connected
//};
//
//const std::vector<GameBoard::CritFunction> GameBoard::CityCriteria =
//{
//    &GameBoard::Crit_isNodeUpgradeAble
//};
//
//const std::vector<GameBoard::CritFunction> GameBoard::RoadCriteria = 
//{
//    &GameBoard::Crit_isFreeEdge,&GameBoard::Crit_Edge_Connected
//};



bool GameBoard::Crit_isFreeNode(Coordinate in_coord, Player * in_player) const
{
    return (nodemap.at(in_coord)->GetNodeOwner() == nullptr);
}
bool GameBoard::Crit_Distance( Coordinate in_coord, Player*  in_player) const
{
    return (nodemap.at(in_coord)->GetNodeOwner() == in_player);
}
bool GameBoard::Crit_Node_Connected( Coordinate in_coord, Player* in_player) const
{
    return (edgemap.at(in_coord)->GetEdgeOwner() == nullptr);
}



const std::vector<GameBoard::CritFunction>& GameBoard::GetSettlementCriteriaFunction() const
{
    return SettlementCriteria;
}
const std::vector<GameBoard::CritFunction>& GameBoard::GetCityCriteriaFunction() const
{
    return CityCriteria;
}
const std::vector<GameBoard::CritFunction>& GameBoard::GetRoadCriteriaFunction() const
{
    return RoadCriteria;
}



void GameBoard::BuildSettlementFunction(Coordinate in_coord, Player* in_player,Building::BuildingTypes in_type)
{
    nodemap[in_coord]->SetNodeOwner(in_player);
    nodemap[in_coord]->SetNodeBuilding(in_type);
}
    
void GameBoard::UpgradeSettlementFunction(Coordinate in_coord, Player* in_player,Building::BuildingTypes in_type)
{
    nodemap[in_coord]->SetNodeBuilding(in_type);
}

void GameBoard::BuildRoadFunction(Coordinate in_coord, Player* in_player,Building::BuildingTypes in_type)
{
    edgemap[in_coord]->SetEdgeOwner(in_player);
    edgemap[in_coord]->SetEdgeBuilding(in_type);
}





GameBoard::BuildFunction GameBoard::GetSettlementBuildFunction() const
{
    return BuildSettlement;
}    

GameBoard::BuildFunction GameBoard::GetUpgradeSettlementFunction() const
{
    return UpgradeSettlement;
}
GameBoard::BuildFunction GameBoard::GetRoadBuildFunction() const
{   
    return BuildRoad;
}













const Coordinate GameBoard::id_to_coord(int in_id,Building::BuildingTypes in_type) const
{
    switch(in_type)
    {
        case Building::BuildingTypes::SETTLEMENT :
            {
                for(auto coord_node_pair : nodemap)
                {
                    if(coord_node_pair.second->GetNodeId() == in_id)
                    {
                        return coord_node_pair.first;
                    }
                }
                printf("\n:(((\n");
            }

        //not needed because this is the same as settlement
        //case Building::BuildingTypes::CITY : 

        case Building::BuildingTypes::ROAD :
            {
                    for(auto coord_edge_pair : edgemap)
                    {
                        if(coord_edge_pair.second->GetEdgeId() == in_id)
                        {
                            return coord_edge_pair.first;
                        }
                    }
                    printf("\n:(((\n");
            }
    }
}



//OTC Constructor
GameBoard::GameBoard(std::vector<std::set<Resource>> in_preset) : resource_types_for_tiles(in_preset), SettlementCriteria{&Crit_isFreeNode,&Crit_Distance,&Crit_Node_Connected}, CityCriteria{&Crit_isNodeUpgradeAble},RoadCriteria{&Crit_isFreeEdge,&Crit_Edge_Connected},BuildSettlement{&BuildSettlementFunction},UpgradeSettlement{&UpgradeSettlementFunction},BuildRoad{&BuildRoadFunction}
{
    //MAJOR TODO lekezelni hogy van-e preset (ha nem akkor majd randgen)


    //for harbor creation
    srand(time(0));
    //Runs for the number of lines it needs to generate
    for(int i = 0;i < 2*BOARD_SIDE_LENGTH-1;i++)
    {
        GenerateLine(i);
    }

    //Sets harbors
    for(auto iter = edgemap.begin();iter != edgemap.end();iter++)
    {
        bool is_coastal = false;
        if((iter->second->GetNodeN_modif(0)->GetEdgeCount() == 2) || (iter->second->GetNodeN_modif(1)->GetEdgeCount() == 2))
        {
            is_coastal = true;
        }
        
        if(is_coastal && ((rand() % 10) == 0)) //TODO ide egy random feltetel hogy mikor es milyen resource + rate
        {
            //debug
            Resource R(BRICK);
            int rate = 2;

            iter->second->GetNodeN_modif(0)->SetHarbor(R,rate);
            iter->second->GetNodeN_modif(1)->SetHarbor(R,rate);
        }
    }
}


//Calculate functions:

//Calculates the coordinate of the tile it needs to BEGIN generating the in_line_num-th line 
Coordinate GameBoard::CalcBegin(int in_line_num)
{
    int tempx = in_line_num;
    int tempy = (in_line_num < BOARD_SIDE_LENGTH) ? 0 : (in_line_num-BOARD_SIDE_LENGTH+1);
    Coordinate ret_coord(tempx,tempy);
    return ret_coord; 
}
//Calculates the coordinate of the tile it needs to END generating the in_line_num-th line 
Coordinate GameBoard::CalcEnd(int in_line_num)  //! Ezt gondold at meg egy kicsit
{
    
    int tempx = in_line_num;
    int tempy = min((2*BOARD_SIDE_LENGTH-1),(in_line_num+BOARD_SIDE_LENGTH));
    Coordinate ret_coord(tempx,tempy);
    return ret_coord; 
}



//Generates the in_line_num-th line
void GameBoard::GenerateLine(int in_line_num)
{
    
    Coordinate line_begin = CalcBegin(in_line_num);
    Coordinate line_end = CalcEnd(in_line_num);
    
    //Generates tiles in the line from left to right
    //note: ez jofele iteracio mert nem egy valami elemein megyunk vegig
    for(Coordinate cur = line_begin;cur != line_end;cur.y++)
    {
        
        //Does multiple things
        //Coordinate-base transformation on cur
        //Generates a tile, calling its OTC Constructor, with:
        //the transformed cur
        //the resource-types for the cur tile, and advances the vector
        //Adds the new tile into the GameBoard's tilemap 

        //note1: Function emplace could be called, instead of Add_to_tilemap
        //the latter was chosen for readabilty 

        //note2: This could be one line, but this execution follows the philosophy
        //of only calling constructors when they are guaranteed to not throw an error
             
        //TODO random
        Tile* tile_toadd = new Tile(this,cur.BigToSmall(),(resource_types_for_tiles[rstpindex++]),9);
        std::pair coord_tile_toadd = std::make_pair(cur,tile_toadd);
        Add_to_tilemap(coord_tile_toadd);        
    }
}

int GameBoard::Get_rstpindex() const 
{
    return rstpindex;
}

void GameBoard::Set_rstpindex(const int in_value)
{
    rstpindex = in_value;
}


const std::map<Coordinate,Node*>& GameBoard::Get_nodemap() const 
{
    return nodemap;
}

void GameBoard::Add_to_nodemap(const std::pair<Coordinate,Node*> in_node)
{
    nodemap.insert(in_node);
}



const std::map<Coordinate,Edge*>& GameBoard::Get_edgemap() const 
{
    return edgemap;
}

void GameBoard::Add_to_edgemap(const std::pair<Coordinate,Edge*> in_edge)
{
    edgemap.insert(in_edge);
}



const std::map<Coordinate,Tile*>& GameBoard::Get_tilemap() const 
{
    return tilemap;
}

void GameBoard::Add_to_tilemap(const std::pair<Coordinate,Tile*> in_tile)
{
    tilemap.insert(in_tile);
}

//felig teszt
void GameBoard::PrintHarbor() const
{
    for(auto node : nodemap)
    {
        if(node.second->IsHarbor())
        {
            printf("Harbor at Node x: %d y: %d\n",node.second->GetNodePos().GetX(),node.second->GetNodePos().GetY());
        }
    }
}





