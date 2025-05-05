#include "gameboard.h"


//OTC Constructor
GameBoard::GameBoard(std::vector<std::set<Resource>> in_preset) : resource_types_for_tiles(in_preset)
{
    //MAJOR TODO lekezelni hogy van-e preset (ha nem akkor majd randgen)

    //Runs for the number of lines it needs to generate
    for(int i = 0;i < 2*BOARD_SIDE_LENGTH-1;i++)
    {
        GenerateLine(i);
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
             
        Tile* tile_toadd = new Tile(this,cur.BigToSmall(),(resource_types_for_tiles[rstpindex++]));
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
