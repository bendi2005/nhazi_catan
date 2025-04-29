#include "gameboard.h"

//TODO document this :downarrow:
std::vector<Coordinate> GameBoard::EdgePos = {Coordinate(-2,-1),Coordinate(-1,1),Coordinate(1,2),Coordinate(2,1),Coordinate(1,-1),Coordinate(-1,2)};
std::vector<Coordinate> GameBoard::NodePos = {Coordinate(-2,-2),Coordinate(-2,0),Coordinate(0,2),Coordinate(2,2),Coordinate(2,0 ),Coordinate(0,-2)};
int main()
{
    //Create GameBoard
    GameBoard g;
    

}