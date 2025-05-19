#include "../include/edges.h"
int Edge::next_edge_id = 0;


//OTC Constructor
Edge::Edge(Node* c1,Node* c2) : nodes_of_edge(c1,c2), edge_id(next_edge_id++),owner_edge(nullptr),building_type_edge(Building::BuildingTypes::EMPTY),pointer_building_edge(nullptr) //I have a bad feeling about this
{}


Coordinate Edge::GetPos() const 
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


sf::RectangleShape Edge::MakeEdgeImage()
{
    sf::Vector2f dir = -(GetNodeN_modif(0)->GetNodePos().ScaledOrtoOrigoOffsetPos() - GetNodeN_modif(1)->GetNodePos().ScaledOrtoOrigoOffsetPos());
    float len = sqrt(dir.x*dir.x + dir.y*dir.y);
    sf::RectangleShape ret_edge(sf::Vector2f{len,EDGE_THICKNESS});

    ret_edge.setPosition(GetNodeN_modif(0)->GetNodePos().ScaledOrtoOrigoOffsetPos());
    ret_edge.setFillColor(GetColorFromOwner());

    


    float angle = atan2(dir.y,dir.x) * RAD_TO_DEG;
    ret_edge.setRotation(sf::degrees(angle));

    
    return ret_edge;
}


sf::Vector2f Edge::GetMidPoint()
{
    return {((GetNodeN_modif(0)->GetNodePos().ScaledOrtoOrigoOffsetPos().x+GetNodeN_modif(1)->GetNodePos().ScaledOrtoOrigoOffsetPos().x)/2.0f), ((GetNodeN_modif(0)->GetNodePos().ScaledOrtoOrigoOffsetPos().y+GetNodeN_modif(1)->GetNodePos().ScaledOrtoOrigoOffsetPos().y)/2.0f)};
}

sf::Color Edge::GetColorFromOwner()
{
    if(!owner_edge)
    {
        return sf::Color(204, 102, 153,255);
    } else 
    {
        int hash = 0;

        for (char c : owner_edge->GetName())
        {
            hash = (hash * 31) + static_cast<uint8_t>(c);
        }

        int r = (hash >> 0) & 0xFF;
        int g = (hash >> 8) & 0xFF;
        int b = (hash >> 16) & 0xFF;

        return sf::Color(r,g,b,255);
    }
}


