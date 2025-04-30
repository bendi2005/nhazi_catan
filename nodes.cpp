#include "nodes.h"
#include "edges.h"
#include "gameboard.h"
Node::Node()
{
    printf("Node constructor default called, ezt se kene nagyon hivogatni");  
}
Node::Node(Coordinate in_coord,int in_i,GameBoard* in_p_GB) : pos(in_coord),p_GB(in_p_GB)
{
    
    in_i++; // ez csak azert van hogy kussoljon
    //ha vektor lenne
    //resources.reserve(HOW_MANY_RESOURCES_DOES_A_NODE_HAVE_MAX);
    own_edges.reserve(SIDE_COUNT);
    for(auto node_element : GetNeighbours())
    {
            //munka
            //uj Edge(node1,node2)
            //thisnek az edge
            //hitnek az edge

            
            Edge* E = new Edge(pos,node_element->pos);
            p_GB->edgemap.emplace((E->GetPos(),E));
            

            own_edges.push_back(E);
            node_element->own_edges.push_back(E);


            //nem lehet 1sor mert kell az uj edge :(((
            //p_GB->edgemap.emplace(pos+Tile::EdgePos[i],new Edge(pos,it->first))
    }
    
    
    ////itt amugy szerintem lehetne az is hogy mindig az i. edik (ami az i+1edik erted kovetkezo)
    ////elt legeneraljuk de aa nem egyszerubb ez:
//
//
    //
    ////auto& e_map = in_p_GB->edgemap;


    
}   
void Node::AddResource(char in_resource)
{
    resources.insert(in_resource); 
}

std::vector<Node*> Node::GetNeighbours()
{
    std::vector<Node*> ret_vec;
    ret_vec.reserve(6);
    auto& n_map = p_GB->nodemap;
    for(int i =0;i<6;i++)
    {
        auto it = n_map.find(pos+Tile::NodePos[i]);
        if(it != n_map.end())
        {
            ret_vec.push_back(it->second);
            ////munka
            //// uj Edge(node1,node2)
            //// thisnek az edge
            ////hitnek az edge
//
            //
            //Edge* E = new Edge(pos,it->first);
            //p_GB->edgemap.emplace(pos+Tile::EdgePos[i],E);
            //
//
            //own_edges.push_back(E);
            //it->second->own_edges.push_back(E);
//
//
            ////nem lehet 1sor mert kell az uj edge :(((
            ////p_GB->edgemap.emplace(pos+Tile::EdgePos[i],new Edge(pos,it->first));
            
        }
    }
    return ret_vec;
    
}