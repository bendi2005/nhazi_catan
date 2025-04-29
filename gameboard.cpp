#include "gameboard.h"


//Constructor of GameBoard
GameBoard::GameBoard()
{
    //ez az 5 
    for(int i = 0;i <= 2*SIDE_LENGHT-1;i++)
    {
        GenerateLine(i);
    }

}


Coordinate GameBoard::CalcBegin(int in_line_num)
{
    int tempx = in_line_num;
    int tempy = (in_line_num < SIDE_LENGHT) ? 0 : (in_line_num-SIDE_LENGHT+1);
    Coordinate ret_coord(tempx,tempy);
    return ret_coord; 
}

Coordinate GameBoard::CalcEnd(int in_line_num)  //! Ezt gondold at meg egy kicsit
{
    int tempx = in_line_num;
    int tempy = min((2*SIDE_LENGHT-1),(in_line_num+SIDE_LENGHT));
    Coordinate ret_coord(tempx,tempy);
    return ret_coord; 
}

void GameBoard::GenerateLine(int in_line_num)
{
    Coordinate line_begin = CalcBegin(in_line_num);
    Coordinate line_end = CalcEnd(in_line_num);
    for(Coordinate cur = line_begin;cur != line_end;cur.GoRight())
    {
        Tile* T = new Tile(this,cur.BigToSmall()); //TODO delete this with auto
        tilemap.insert(std::make_pair(cur,T));
    }
    


}