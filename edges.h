#pragma once
#include "coord.h"
#include <stdio.h>
class Edge
{
private:
    Edge();
public:
    Coordinate node_1_pos;
    Coordinate node_2_pos;

    
    //ez amugy szerintem rohadtul nem kell
    Coordinate edge_pos;
    
    
    const Coordinate GetPos() const;
    
    Edge(Coordinate,Coordinate);


};