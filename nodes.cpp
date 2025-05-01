#include "nodes.h"
#include "edges.h"
#include "gameboard.h"
Node::Node()
{
    printf("Node constructor default called, ezt se kene nagyon hivogatni");  
}
Node::Node(Coordinate in_coord,GameBoard* in_p_GB) : pos(in_coord),p_GB(in_p_GB)
{
    
    own_edges.reserve(SHAPE_NODE_COUNT);
    auto negs = GetNeighbours();
    printf("Negs found: %llu \n",negs.size());
    //for(auto node_element : GetNeighbours())
    for(auto element : negs)
    {
          
            
            Edge* E = new Edge(pos,element->pos);
            p_GB->edgemap.emplace(std::make_pair(E->GetPos(),E));
            

            own_edges.push_back(E);
            element->own_edges.push_back(E);
           
    }

}   
void Node::AddResource(Resource in_resource)
{
    node_resource_types.insert(in_resource); 
}

std::vector<Node*> Node::GetNeighbours()
{
    
    std::vector<Node*> ret_vec;
    ret_vec.reserve(SHAPE_NODE_COUNT);
    
    auto& n_map = (p_GB->nodemap);
    
    for(int i =0;i<SHAPE_NODE_COUNT;i++)
    {
        printf("\n%d",i);
        Coordinate cur(pos+Tile::NodePos[i]);
        auto it = n_map.find(cur);
    
        //if(contains)
        if(it != n_map.end())
        {

            ret_vec.push_back(it->second);


            
            //Edge* E = new Edge(pos,it->first);
            //p_GB->edgemap.emplace(pos+Tile::EdgePos[i],E);
//
            //own_edges.push_back(E);
            //it->second->own_edges.push_back(E);            
        }

    }
    return ret_vec;
    
}