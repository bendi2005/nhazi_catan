#include "gameboard.h"
#include <random>

//OTC Constructor
GameBoard::GameBoard(std::vector<std::set<Resource>> in_preset_resource,std::vector<int> in_preset_dicenum) : resource_types_for_tiles(in_preset_resource),dicenum_for_tiles(in_preset_dicenum), SettlementCriteria{&Crit_isFreeNode,&Crit_Distance,&Crit_Node_Connected}, CityCriteria{&Crit_isNodeUpgradeAble},RoadCriteria{&Crit_isFreeEdge,&Crit_Edge_Connected},BuildSettlement{&BuildSettlementFunction},UpgradeSettlement{&UpgradeSettlementFunction},BuildRoad{&BuildRoadFunction}
{
    //MAJOR TODO lekezelni hogy van-e preset (ha nem akkor majd randgen)
    //szerintem ugy lesz hogy itt fel lesz toltve az amihez nincs preset
    //meaning nem tile-onkent van random gen



    //for harbor creation and dice rolling
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
    
    //trivial
    Coordinate line_begin = CalcBegin(in_line_num);
    Coordinate line_end = CalcEnd(in_line_num);
    
    //Generates tiles in the line from left to right
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
             
        //TODO random (?)
        Tile* tile_toadd = new Tile(this,cur.BigToSmall(),(resource_types_for_tiles[rstpindex++]),dicenum_for_tiles[dienumindex++]);
        std::pair coord_tile_toadd = std::make_pair(cur,tile_toadd);
        Add_to_tilemap(coord_tile_toadd);        
    }
}


//Rolls 2 dice and returns their sum
int GameBoard::RollDice() const
{
    return ((rand() % 6 + 1)  + (rand() % 6 + 1));
}

//Getter and Setter for rstpindex

int GameBoard::Get_rstpindex() const 
{
    return rstpindex;
}

void GameBoard::Set_rstpindex(const int in_value)
{
    rstpindex = in_value;
}


//Getters and Setters for maps

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


//Criteria Functions

//Node

//Checks if there is anything on the node (if yes, its not free)
bool GameBoard::Crit_isFreeNode(Coordinate in_coord, Player * in_player) const
{
    return (nodemap.at(in_coord)->GetNodeOwner() == nullptr);
}

//Refer to "distance rule" 
//Getneighbours() on current node and if every neighbouring node's  
//owner_node* is a nullptr the distance criteria is fulfilled
bool GameBoard::Crit_Distance( Coordinate in_coord, Player*  in_player) const
{
    for(auto negnode : nodemap.at(in_coord)->GetNeighbours())
    {
        if(negnode->GetNodeOwner() != nullptr)
        {
            return false;
        }
    }
    return true; 
}


//Checks if node is connected to any nearb road
bool GameBoard::Crit_Node_Connected(Coordinate in_coord, Player* in_player) const
{
    for(auto elementedge : nodemap.at(in_coord)->GetOwnEdges())
    {
        if(elementedge->GetEdgeOwner() == in_player)
        {
            return true;
        }
    }
    return false;
}



//Edge

//Checks if there is anything on the edge (if yes, its not free)
bool GameBoard::Crit_isFreeEdge(Coordinate in_coord,Player* in_player) const 
{
    return edgemap.at(in_coord)->GetEdgeOwner() == nullptr;
}

//Checks if edge is connected to any nearby Road or Settlement
//One of its nodes is a Settlement (owned by in_player) OR One of its nodes' Edge is a Road (owned by in_player) 
bool GameBoard::Crit_Edge_Connected(Coordinate in_coord,Player* in_player) const 
{
    //ez nem tudom hogy 1 sor legyen-e vagy olvashatosag miatt tobb

    //One of its nodes is a Settlement
    if(edgemap.at(in_coord)->GetNodesOfEdge().first->GetNodeOwner() == in_player || edgemap.at(in_coord)->GetNodesOfEdge().second->GetNodeOwner() == in_player)
    {
        return true;
    }

    //One of its nodes' Edge is a Road

    //First node
    for(auto idknode : edgemap.at(in_coord)->GetNodesOfEdge().first->GetOwnEdges())
    {
        if(idknode->GetEdgeOwner() == in_player)
        {
            return true;
        }
    }

    //Second node
    for(auto idknode : edgemap.at(in_coord)->GetNodesOfEdge().second->GetOwnEdges())
    {
        if(idknode->GetEdgeOwner() == in_player)
        {
            return true;
        }
    }
    return false;
}


//City

//Checks if node is owned by player trying to upgrade
bool GameBoard::Crit_isNodeUpgradeAble(Coordinate in_coord,Player* in_player) const
{
    return nodemap.at(in_coord)->GetNodeOwner() == in_player;
}




//Getters for Critfunctions

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



//Build functions

//Builds Settlement
void GameBoard::BuildSettlementFunction(Coordinate in_coord, Player* in_player,Building::BuildingTypes in_type)
{
    nodemap[in_coord]->SetNodeOwner(in_player);
    Settlement* S = new Settlement;
    nodemap[in_coord]->SetNodeBuilding(in_type);
}
    
//Upgrades Settlement (=Builds City)  
void GameBoard::UpgradeSettlementFunction(Coordinate in_coord, Player* in_player,Building::BuildingTypes in_type)
{
    nodemap[in_coord]->SetNodeBuilding(in_type);
}

//Builds Road
void GameBoard::BuildRoadFunction(Coordinate in_coord, Player* in_player,Building::BuildingTypes in_type)
{
    edgemap[in_coord]->SetEdgeOwner(in_player);
    edgemap[in_coord]->SetEdgeBuilding(in_type);
}



//Getters for BuildFunctions

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


//Converts id to coordinate, depending on if its a node or edge coord
const Coordinate GameBoard::id_to_coord(int in_id,Building::BuildingTypes in_type) const
{
    //node or edge?
    switch(in_type)
    {
        //node (Settlement or City)
        case Building::BuildingTypes::SETTLEMENT :
        case Building::BuildingTypes::CITY :
            {
                for(auto coord_node_pair : nodemap)
                {
                    if(coord_node_pair.second->GetNodeId() == in_id)
                    {
                        return coord_node_pair.first;
                    }
                }
            }
        break;
        //edge
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
        break;
        default :
            printf("baj van");
        break;
    }
}


void GameBoard::DistributeResources()
{
    int sum = RollDice();
    for(auto geci : nodemap)
    {
        for(auto fasz : geci.second->GetTilesOfNode())
        {
            if(geci.second->GetNodeOwner() != nullptr && fasz->GetDieNum() == sum)
            {
                fasz->GiveResources(geci.second->GetNodeOwner(),geci.second->GetNodePointerBuilding()->ProduceResource());
            }
        }

    }


}


