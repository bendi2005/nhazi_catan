#pragma once
#include "coord.h"
#include <stdio.h>
#include <set>
#include "nodes.h"
class Node;
class GameBoard;
class Tile;
class Edge
{
private:
    //Coordinate& node_1;
    //Coordinate& node_2;
    std::pair<Node&,Node&> nodes_of_edge;
    
public:
    //only for debugging
    Edge() = delete;    

    Edge(Node&,Node&);
    

    
    const Coordinate GetPos() const;

    Node& GetNodeN_modif(int);
};