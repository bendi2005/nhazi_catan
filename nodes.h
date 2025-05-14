#pragma once
#include "coord.h"
#include "magic_const.h"
#include "edges.h"
#include <vector>
#include "building.h"

#include <set>
//TADA
//Harbor
//if is_there, owner can exchange <rate> of <harbor_resource_type> for 1 of chosen resource 
struct str_HarborInfo
{
    bool is_there = false;
    Resource harbor_resource_type;
    int rate;
};

//Forward declarations
class GameBoard;
class Tile;
class Player;
class Edge;
class Node
{
private:

    static int next_node_id;
    
    //this is the same thing as Tile::NodePos
    //note: see devnotes about this
    static std::vector<Coordinate> SearchDirections;
    
    //i think this is only useful for debugging but not sure
    int edgecount;
    
    //preset
    str_HarborInfo harborinfo = {false,BRICK,100};


    

    //Properties of Node
    int node_id;
    Coordinate pos;
    GameBoard* p_GB;
    
    std::set<Tile*> tiles_of_node;
    std::vector<Edge*> own_edges;

    Player* owner_node;    
    Building::BuildingTypes building_type_node;
    Building* pointer_building_node;

public: 
    //OTC Constructor
    Node(Coordinate,GameBoard*);
    
    //nem fog kelleni debug utan (???)
    Node() = delete;

    //Getter for pos
    const Coordinate GetNodePos() const;

    //Getter for id
    int GetNodeId() const;
    
    //Getter for EdgeCount
    int GetEdgeCount() const;
    

    




    //desc in cpp
    std::vector<Node*> GetNeighbours();

    void AddTileToNode(Tile*);
    const std::set<Tile*> GetTilesOfNode() const;

    //Harbor related
    void SetHarbor(Resource,int);
    bool IsHarbor();

    //Getter for OwnEdges
    const std::vector<Edge*> GetOwnEdges() const;
       
    //Getter and Setter for NodeOwner
    Player* GetNodeOwner() const;
    void SetNodeOwner(Player*);
    
    //Builds on Node
    void SetNodeBuilding(const Building::BuildingTypes);
    void SetNodePointerBuilding(Building*);

    Building* GetNodePointerBuilding();



};