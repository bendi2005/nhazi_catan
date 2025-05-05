#pragma once
#include "coord.h"
#include <stdio.h>
#include <set>
class Node;
class GameBoard;
class Tile;
class Edge
{
private:
    Coordinate node_1_pos;
    Coordinate node_2_pos;

public:
    //only for debugging
    Edge();    

    Edge(const Coordinate&,const Coordinate&);
    
    
    const Coordinate GetPos() const;
};