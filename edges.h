#pragma once
#include "coord.h"
#include <stdio.h>
#include <set>
#include "nodes.h"
#include "player.h"
#include "building.h"

class Edge
{
private:
    //Coordinate& node_1;
    //Coordinate& node_2;
    std::pair<Node*,Node*> nodes_of_edge;
    static int next_edge_id;
    int edge_id;   

    Player* owner_edge;
    Building::BuildingTypes building_edge; 

public:
    //only for debugging
    Edge() = delete;    

    Edge(Node*,Node*);
    

    
    const Coordinate GetPos() const;

    Node* GetNodeN_modif(int);

    int GetEdgeId() const;
    
    
    
    void SetEdgeOwner(Player*);
    const Player* GetEdgeOwner() const;
    
    
    
    void SetEdgeBuilding(Building::BuildingTypes);
    
    
};