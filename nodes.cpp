#include "nodes.h"
#include "edges.h"
#include "gameboard.h"

std::vector<Coordinate> Node::SearchDirections = {Coordinate(-2,-2),Coordinate(-2,0),Coordinate(0,2),Coordinate(2,2),Coordinate(2,0 ),Coordinate(0,-2)};

Node::Node()
{
    printf("Node constructor default called, ezt se kene nagyon hivogatni");  
}


//OTC Constructor
Node::Node(Coordinate in_coord,GameBoard* in_p_GB) : pos(in_coord),p_GB(in_p_GB)
{
    own_edges.reserve(SHAPE_NODE_COUNT);
    auto negs = GetNeighbours();
    
    //for(auto node_element : GetNeighbours())
    for(auto element : negs)
    {       
        //same thing as in tiles.cpp
        Edge* E = new Edge(pos,element->pos);
        std::pair<Coordinate,Edge*> cor_edge_pair_toadd = std::make_pair(E->GetPos(),E);
        p_GB->Add_to_edgemap(cor_edge_pair_toadd);
        
        //Add edge to this node and the neighbour node
        own_edges.push_back(E);
        element->own_edges.push_back(E);
    }
}   

//trivial
void Node::AddResourceToNode(Resource in_resource)
{
    node_resource_types.insert(in_resource); 
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
