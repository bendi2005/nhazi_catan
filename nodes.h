#pragma once
#include "coord.h"
#include "magic_const.h"
#include "resource.h"
#include <vector>
#include <set>
class Edge;
class GameBoard;
class Node
{
private:

    //this is the same thing as Tile::NodePos
    //note: see devnotes about this
    static std::vector<Coordinate> SearchDirections;
    
    //nem fog kelleni debug utan
    Node();

    //trivial
    std::set<Resource> node_resource_types;
    Coordinate pos;
    GameBoard* p_GB;
    std::vector<Edge*> own_edges; //ez honnan tudja hogy mi az az Edge lol?




    //OTC Constructor
    


    

    


public: 
    Node(Coordinate,GameBoard*);
    std::vector<Node*> GetNeighbours();
    void AddResourceToNode(Resource);
};