#pragma once
#include "coord.h"
#include <stdio.h>

class Node;
class GameBoard;
class Tile;
class Edge
{
private:
Edge();    
public:

    Coordinate node_1_pos;
    Coordinate node_2_pos;

    
    //ez amugy szerintem rohadtul nem kell
    
    
    const Coordinate GetPos() const;
    
    Edge(const Coordinate&,const Coordinate&);


};