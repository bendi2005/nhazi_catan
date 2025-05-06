#include "edges.h"
Edge::Edge(Node* c1,Node* c2) : nodes_of_edge(c1,c2) //I have a bad feeling about this
{
    
}
const Coordinate Edge::GetPos() const 
{
    return Coordinate(((nodes_of_edge.first->GetNodePos().x+nodes_of_edge.second->GetNodePos().x)/2),(nodes_of_edge.first->GetNodePos().y+nodes_of_edge.second->GetNodePos().y)/2);
}

Node* Edge::GetNodeN_modif(int N) 
{
    return N == 0 ? nodes_of_edge.first : nodes_of_edge.second;
}