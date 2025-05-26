#include "../include/nodes.h"
#include "../include/gameboard.h"

int Node::next_node_id = 0;
//set SearchDirections
std::vector<Coordinate> Node::SearchDirections = {Coordinate(-2,-2),Coordinate(-2,0),Coordinate(0,2),Coordinate(2,2),Coordinate(2,0 ),Coordinate(0,-2)};

//OTC Constructor
Node::Node(Coordinate in_coord,GameBoard* in_p_GB) : node_id(next_node_id++),pos(in_coord),p_GB(in_p_GB),owner_node(nullptr),building_type_node(Building::BuildingTypes::EMPTY),pointer_building_node(nullptr)
{
    own_edges.reserve(SHAPE_EDGE_COUNT);
    auto negs = GetNeighbours();
    
    for(auto element : negs)
    {       
        //same thing as in tiles.cpp
        Edge* E = new Edge(this,element);
        std::pair<Coordinate,Edge*> cor_edge_pair_toadd = std::make_pair(E->GetPos(),E);
        p_GB->Add_to_edgemap(cor_edge_pair_toadd);
        
        //Add edge to this node and the neighbour node
        own_edges.push_back(E);
        edgecount++;
        element->own_edges.push_back(E);
        
        //todo setter
        element->edgecount++;
    }
}   

bool Node::InClickRadius(const sf::Vector2i click_pos)
{
    return ((abs(pos.ScaledOrtoOrigoOffsetPos().x-click_pos.x)) <= CLICK_RADIUS && (abs(pos.ScaledOrtoOrigoOffsetPos().y-click_pos.y)) <= CLICK_RADIUS);
}



//Getter for pos
Coordinate Node::GetNodePos() const
{
    return pos;
}

//Getter for id
int Node::GetNodeId() const
{
    return node_id;
}

//Getter for  OwnEdges
const std::vector<Edge*> Node::GetOwnEdges() const
{
    return own_edges;
}

//Getter for EdgeCount
int Node::GetEdgeCount() const
{
    return edgecount;
}


//Getter and Setter for NodeOwner
Player* Node::GetNodeOwner() const
{
    return owner_node;
}

void Node::SetNodeOwner(Player*  in_player)
{
    owner_node = in_player;
}


//trivial
void Node::AddTileToNode(Tile* in_tile)
{
    tiles_of_node.insert(in_tile);
    return;
}

const std::set<Tile*> Node::GetTilesOfNode() const
{
    return tiles_of_node;
}


//Harbor related

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

void Node::SetNodeBuilding(const Building::BuildingTypes in_build )
{
    building_type_node = in_build;
}

void Node::SetNodePointerBuilding(Building* in_build)
{
    pointer_building_node = in_build;
}

Building* Node::GetNodePointerBuilding()
{
    return pointer_building_node;
}

sf::Color Node::GetColorFromOwner()
{
    if(!owner_node)
    {
        return sf::Color::White;
    } else 
    {
        return PLAYER_COLORS[owner_node->GetPlayerId()];
    }
}

sf::CircleShape Node::MakeNodeImage()
{
    sf::CircleShape node_ret(NODE_SIZE,50);
    
    node_ret.setOrigin({NODE_SIZE,NODE_SIZE});
    node_ret.setPosition(pos.ScaledOrtoOrigoOffsetPos());
    node_ret.setFillColor(GetColorFromOwner());
    if(this->IsHarbor())
    {   
        node_ret.setOutlineThickness(4);
        node_ret.setOutlineColor(p_GB->GeneralColorByResource(harborinfo.harbor_resource_type));
    }
    
    return node_ret;
}



