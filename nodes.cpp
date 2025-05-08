#include "nodes.h"
#include "gameboard.h"

std::vector<Coordinate> Node::SearchDirections = {Coordinate(-2,-2),Coordinate(-2,0),Coordinate(0,2),Coordinate(2,2),Coordinate(2,0 ),Coordinate(0,-2)};




//OTC Constructor
Node::Node(Coordinate in_coord,GameBoard* in_p_GB) : node_id(next_node_id++),pos(in_coord),p_GB(in_p_GB),owner_node(nullptr),building_node(Building::BuildingTypes::EMPTY)
{
    own_edges.reserve(SHAPE_NODE_COUNT);
    auto negs = GetNeighbours();
    
    for(auto element : negs)
    {       
        //same thing as in tiles.cpp
        Edge* E = new Edge(this,element);
        std::pair<Coordinate,Edge*> cor_edge_pair_toadd = std::make_pair(E->GetPos(),E);
        p_GB->Add_to_edgemap(cor_edge_pair_toadd);
        edgecount++;
        //Add edge to this node and the neighbour node
        own_edges.push_back(E);
        element->own_edges.push_back(E);
    }
}   



int Node::GetEdgeCount() const
{
    return edgecount;
}

void Node::IncEdgeCount()
{
    edgecount++;
}


//trivial
void Node::AddTileToNode(Tile* in_tile)
{
    tiles_of_node.insert(in_tile);
    return;
}

const Coordinate Node::GetNodePos() const
{
    return pos;
}


void Node::SetHarbor(Resource in_resource_type,int in_rate)
{
    harborinfo.is_there = true;
    harborinfo.harbor_resource_type = in_resource_type;
    harborinfo.rate = in_rate;
}
bool Node::IsHarbor()
{
    return harborinfo.is_there;
}


//Checks all 6 directions, and if it finds a node there 
//its a neighbour: adds it to list and creates edge between them
std::vector<Node*> Node::GetNeighbours()
{
    
    std::vector<Node*> ret_vec;
    ret_vec.reserve(SHAPE_NODE_COUNT);
    
    auto nmap = p_GB->Get_nodemap();
    for(int i = 0;i<SHAPE_NODE_COUNT;i++)
    {
        Coordinate cur(pos+SearchDirections[i]);
        auto it = nmap.find(cur);
    
        //contains
        if(it != nmap.end())
        {

            ret_vec.push_back(it->second);         
        }
    }
    return ret_vec;   
}

int Node::GetNodeId() const
{
    return node_id;
}

void Node::SetNodeOwner(Player*  in_player)
{
    owner_node = in_player;
}

    
void Node::SetNodeBuilding(Building::BuildingTypes in_type)
{
    building_node = in_type;
}

const Player* Node::GetNodeOwner() const
{
    return owner_node;
}
