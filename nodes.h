#pragma once
#include "coord.h"
#include "magic_const.h"
#include "edges.h"
#include <vector>
#include "building.h"

#include <set>
struct str_HarborInfo
{
    bool is_there = false;
    Resource harbor_resource_type;
    int rate;
};
class Tile;

class Player;
class Node
{
private:

    //this is the same thing as Tile::NodePos
    //note: see devnotes about this
    static std::vector<Coordinate> SearchDirections;
    int edgecount;
    
    str_HarborInfo harborinfo = {false,BRICK,100};


    

    //trivial
    std::set<Tile*> tiles_of_node;
    Coordinate pos;
    GameBoard* p_GB;
    std::vector<Edge*> own_edges;
    
    static int next_node_id;
    int node_id;
    Player* owner_node;    
    Building::BuildingTypes building_node;

public: 
    //OTC Constructor
    Node(Coordinate,GameBoard*);
    
    std::vector<Node*> GetNeighbours();
    
    const Coordinate GetNodePos() const;

    //nem fog kelleni debug utan
    Node() = delete;

    int GetEdgeCount() const;
    void SetEdgeCount(); //ezt amugy lehet nem hasznaljuk semmire
    void IncEdgeCount(); //ennek az egvilagon semmi ertelme 
    
    void AddTileToNode(Tile*);
    
    void SetHarbor(Resource,int);
    bool IsHarbor();

    int GetNodeId() const;


    
    void SetNodeOwner(Player*);

    
    void SetNodeBuilding(const Building::BuildingTypes);
    
    
};