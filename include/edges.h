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
    //The pointers of the two nodes the edge connects to
    std::pair<Node*,Node*> nodes_of_edge;
    
    //id of edge
    int edge_id;   

    //kerdes labvezhez: ezt megcsinaljam ugy hogy nincs building_type csak a pointer es azt adogatni mindenhol?
    //eleg szenvedos lenne mert mar meg van csinalva building_tpye_edgeel (es ott nem is kell nullptr-t kezelni mert az EMPTY megoldja)

    //Pointer of Player who has a building on the edge (by default nullptr)
    Player* owner_edge;
    //BuildingTypes enum value of the building on the edge (by default EMPTY)
    Building::BuildingTypes building_type_edge; 
    //Pointer to the Building on the edge (by default nullptr)
    Building* pointer_building_edge;

    //id of next edge (increment and set to edge_id)
    static int next_edge_id;


public:
    //Should not be called
    Edge() = delete;    


    //Sets the nodes_of_edge to the parameter nodes, sets the owner_edge,building_type_edge and pointer_building_edge to the default values
    //OTC Constructor
    Edge(Node*,Node*);
    

    //Returns the Coordinate of edge's middle point
    const Coordinate GetPos() const;

    //Gets the nth (0-index) Node* of nodes_of_edge 
    Node* GetNodeN_modif(int);

    //Returns id of Edge
    int GetEdgeId() const;
    
    //Sets Edge's owner to the parameter Player
    void SetEdgeOwner(Player*);
    //Getter for owner_edge
    const Player* GetEdgeOwner() const;
    
    //Getter for nodes_of_edge
    const std::pair<Node*,Node*> GetNodesOfEdge() const;
    
    
    //Sets Edge's building_type_edge
    void SetEdgeBuilding(Building::BuildingTypes);
    //Sets Edge's pointer_building_edge
    void SetEdgePointerBuilding(Building*);

    //Getter for pointer_building_edge
    Building* GetEdgePointerBuilding();

    sf::RectangleShape MakeEdgeImage();

};