#include "gameboard.h"


//OTC Constructor
GameBoard::GameBoard(std::vector<std::set<Resource>> in_preset) : resource_types_for_tiles(in_preset)
{
    //MAJOR TODO lekezelni hogy van-e preset (ha nem akkor majd randgen)

    //Runs for the number of lines it needs to generate
    for(int i = 0;i < 2*SIDE_LENGTH-1;i++)
    {
        GenerateLine(i);
    }
}


//Calculates the coordinate of the tile it needs to BEGIN generating the in_line_num-th line 
Coordinate GameBoard::CalcBegin(int in_line_num)
{
    int tempx = in_line_num;
    int tempy = (in_line_num < SIDE_LENGTH) ? 0 : (in_line_num-SIDE_LENGTH+1);
    Coordinate ret_coord(tempx,tempy);
    return ret_coord; 
}
//Calculates the coordinate of the tile it needs to END generating the in_line_num-th line 
Coordinate GameBoard::CalcEnd(int in_line_num)  //! Ezt gondold at meg egy kicsit
{
    
    int tempx = in_line_num;
    int tempy = min((2*SIDE_LENGTH-1),(in_line_num+SIDE_LENGTH));
    Coordinate ret_coord(tempx,tempy);
    return ret_coord; 
}



//Generates the in_line_num-th line
void GameBoard::GenerateLine(int in_line_num)
{
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
        tilemap.emplace(std::make_pair(cur,new Tile(this,cur.BigToSmall(),&(resource_types_for_tiles[rstpindex++]))));        
    }
}