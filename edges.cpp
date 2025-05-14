#include "edges.h"
int Edge::next_edge_id = 0;


//OTC Constructor
Edge::Edge(Node* c1,Node* c2) : nodes_of_edge(c1,c2), edge_id(next_edge_id++),owner_edge(nullptr),building_type_edge(Building::BuildingTypes::EMPTY),pointer_building_edge(nullptr) //I have a bad feeling about this
{}


const Coordinate Edge::GetPos() const 
{
    return Coordinate(((nodes_of_edge.first->GetNodePos().x+nodes_of_edge.second->GetNodePos().x)/2),(nodes_of_edge.first->GetNodePos().y+nodes_of_edge.second->GetNodePos().y)/2);
}

Node* Edge::GetNodeN_modif(int N) 
{
    return N == 0 ? nodes_of_edge.first : nodes_of_edge.second;
}

int Edge::GetEdgeId() const
{
    return edge_id;
}


const Player* Edge::GetEdgeOwner() const
{
    return owner_edge;
}

void Edge::SetEdgeOwner(Player* in_player)
{
    owner_edge = in_player;
}


void Edge::SetEdgeBuilding(Building::BuildingTypes in_type)
{
    building_type_edge = in_type;
}

void Edge::SetEdgePointerBuilding(Building* in_build)
{   
    pointer_building_edge = in_build;
}



const std::pair<Node*,Node*> Edge::GetNodesOfEdge() const 
{
    return nodes_of_edge;
}

Building* Edge::GetEdgePointerBuilding()
{
    return pointer_building_edge;
}