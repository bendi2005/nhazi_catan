#pragma once
#include "coord.h"
#include "magic_const.h"
#include "resource.h"
#include <vector>
#include <set>
struct str_HarborInfo
{
    bool is_there = false;
    Resource harbor_resource_type;
    int rate;
};
class Edge;
class GameBoard;
class Node
{
private:

    //this is the same thing as Tile::NodePos
    //note: see devnotes about this
    static std::vector<Coordinate> SearchDirections;
    int edgecount;
    str_HarborInfo harborinfo;


    //nem fog kelleni debug utan
    Node();

    //trivial
    std::set<Tile*> tiles_of_node;
    Coordinate pos;
    GameBoard* p_GB;
    std::vector<Edge*> own_edges; //ez honnan tudja hogy mi az az Edge lol?

public: 
    //OTC Constructor
    Node(Coordinate,GameBoard*);
    
    std::vector<Node*> GetNeighbours();
    
    const Coordinate GetNodePos() const;

    

    const int GetEdgeCount() const;
    void SetEdgeCount(); //ezt amugy lehet nem hasznaljuk semmire
    void IncEdgeCount(); //ennek az egvilagon semmi ertelme 
    
    void AddTileToNode(Tile*);
    
    void SetHarbor(Resource,int);
    bool IsHarbor();
};