#include "nodes.h"
#include "edges.h"
#include "gameboard.h"
Node::Node()
{
    printf("Node constructor default called, ezt se kene nagyon hivogatni");  
}
Node::Node(Coordinate in_coord,int in_i,GameBoard* in_p_GB)
{
    pos = in_coord;
    
    //ha megis vektor kene (nem fog)
    //resources.reserve(HOW_MANY_RESOURCES_DOES_A_NODE_HAVE_MAX);
    own_edges.reserve(SIDE_COUNT);

    
    
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