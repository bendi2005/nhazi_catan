#include "gameboard.h"


//Constructor of GameBoard
GameBoard::GameBoard()
{
    //ez az 5 
    for(int i = 0;i < 2*SIDE_LENGTH-1;i++)
    {
        GenerateLine(i);
        printf("\n?\n")
    }

}


Coordinate GameBoard::CalcBegin(int in_line_num)
{
    int tempx = in_line_num;
    int tempy = (in_line_num < SIDE_LENGTH) ? 0 : (in_line_num-SIDE_LENGTH+1);
    Coordinate ret_coord(tempx,tempy);
    
    return ret_coord; 
}

Coordinate GameBoard::CalcEnd(int in_line_num)  //! Ezt gondold at meg egy kicsit
{
    
    int tempx = in_line_num;
    int tempy = min((2*SIDE_LENGTH-1),(in_line_num+SIDE_LENGTH));
    Coordinate ret_coord(tempx,tempy);
    return ret_coord; 
}

void GameBoard::GenerateLine(int in_line_num)
{
    Coordinate line_begin = CalcBegin(in_line_num);
    Coordinate line_end = CalcEnd(in_line_num);
    
    for(Coordinate cur = line_begin;cur != line_end;cur.y++)
    {
        //TODO delete this 
    
        printf("?\n");
        tilemap.emplace(std::make_pair(cur,new Tile(this,cur.BigToSmall())));
        printf("?\n");
        cur.PrintCord();
        
    }
    


}