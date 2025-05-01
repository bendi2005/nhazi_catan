#include "tiles.h"
#include "gameboard.h"
std::vector<Coordinate> Tile::EdgePos = {Coordinate(-2,-1),Coordinate(-1,1),Coordinate(1,2),Coordinate(2,1),Coordinate(1,-1),Coordinate(-1,2)};
std::vector<Coordinate> Tile::NodePos = {Coordinate(-2,-2),Coordinate(-2,0),Coordinate(0,2),Coordinate(2,2),Coordinate(2,0 ),Coordinate(0,-2)};
Tile::Tile(GameBoard* in_p_GB, Coordinate in_center,const std::set<Resource>* in_resource) : pos(in_center), p_GB(in_p_GB)
{
      
    
    
    
    for(const auto& in_resource_element : *in_resource)
    {
        tile_resource_types.emplace(in_resource_element);
    }
    //
    GenerateNodes(p_GB);

}
void Tile::GenerateNodes(GameBoard* in_p_GB)
{
    //note: dont need to handle edge-case where getter returns null
    const std::map<Coordinate,Node*>& n_map = (in_p_GB->Get_nodemap());

    
    //Iterate through all nodes of the tile
    for(int i = 0;i<SHAPE_NODE_COUNT;i++)
    {
        //current node coord
        Coordinate cur(pos+NodePos[i]);
        
        //check if map contains current node
        auto it = n_map.find(cur);
        
        //Contains
        if(it != n_map.end())
        {
            
            PutResourcesIntoNode(it->second);
            
        } 
        //not contain
        else {
            //ezt azert gondold at
            
            PutResourcesIntoNode((in_p_GB->nodemap.emplace(std::make_pair(cur,new Node(cur,in_p_GB))).first)->second);
            
           
        }
    }   
}
void Tile::PutResourcesIntoNode(Node* in_Node) //ha referncia kell akkor sincs nagy baj
{
    for(auto tile_resource : tile_resource_types)
    {
        in_Node->AddResource(tile_resource);   
    }
}

