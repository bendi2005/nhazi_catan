#pragma once
#include "coord.h"
class Edge
{
public:
    Coordinate node_1_pos;
    Coordinate node_2_pos;

    
    //ez amugy szerintem rohadtul nem kell
    Coordinate edge_pos;
    
    Edge();
    Edge(Coordinate,Coordinate);


};