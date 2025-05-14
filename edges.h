#pragma once
#include "coord.h"
#include <stdio.h>
#include <set>
#include "nodes.h"
#include "player.h"
#include "building.h"

class Node;
class Edge
{
private:
    //Coordinate& node_1;
    //Coordinate& node_2;
    std::pair<Node*,Node*> nodes_of_edge;
    
    int edge_id;   

    Player* owner_edge;
    Building::BuildingTypes building_type_edge; 
    Building* pointer_building_edge;


public:
    //only for debugging
    Edge() = delete;    


    //make this private miutan megnezted hogy jo-e az edgegen
    static int next_edge_id;

    //OTC Constructor
    Edge(Node*,Node*);
    

    
    const Coordinate GetPos() const;

    Node* GetNodeN_modif(int);

    int GetEdgeId() const;
    
    
    
    void SetEdgeOwner(Player*);
    const Player* GetEdgeOwner() const;
    
    const std::pair<Node*,Node*> GetNodesOfEdge() const;
    
    
    void SetEdgeBuilding(Building::BuildingTypes);
    void SetEdgePointerBuilding(Building*);

    Building* GetEdgePointerBuilding();

    
};