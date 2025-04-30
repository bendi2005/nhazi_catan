#include "tiles.h"
#include "gameboard.h"
std::vector<Coordinate> Tile::EdgePos = {Coordinate(-2,-1),Coordinate(-1,1),Coordinate(1,2),Coordinate(2,1),Coordinate(1,-1),Coordinate(-1,2)};
std::vector<Coordinate> Tile::NodePos = {Coordinate(-2,-2),Coordinate(-2,0),Coordinate(0,2),Coordinate(2,2),Coordinate(2,0 ),Coordinate(0,-2)};
Tile::Tile(GameBoard* in_p_GB, Coordinate in_center,std::set<char> in_resource) : pos(in_center), p_GB(in_p_GB)
{
      
    //ha vektor
    //tile_resources.reserve(HOW_MANY_RESOURCE_DOES_A_TILE_HAVE);
    
    
    for(const auto& in_resource_element : in_resource)
    {
        tile_resources.emplace(in_resource_element);
    }
    //
    GenerateNodes(p_GB);

}
void Tile::GenerateNodes(GameBoard* in_p_GB)
{
    auto n_map = &(in_p_GB->nodemap);
    //amugy szerintem ez hivogatja a konstruktort

    
    for(int i = 0;i<SIDE_COUNT;i++)
    {
        //current node coord
       
        
       
    
        Coordinate cur(pos+NodePos[i]);
        
        
        //check if map contains current node
        //std::map<Coordinate,Node*>::iterator it = in_p_GB->nodemap.find(cur);
        bool isin = false;
        Node* f;
        for(auto kvp : *n_map)
        {
            if(kvp.first==cur)
            {
                isin = true;
                f=kvp.second;
            }
        }
        
        
        //contain
        //if(it != in_p_GB->nodemap.end())
        if(isin)
        {
            //ember bazdmeg hogy nez ez ki
            
            //PutResourcesIntoNode((it)->second);
            PutResourcesIntoNode(f);
            
        } 
        //not contain
        else {
            //ezt azert gondold at
            
            PutResourcesIntoNode((in_p_GB->nodemap.emplace(std::make_pair(cur,new Node(cur,i,in_p_GB))).first)->second);
            
           
        }
    }   
}
void Tile::PutResourcesIntoNode(Node* in_Node) //ha referncia kell akkor sincs nagy baj
{
    for(auto tile_resource : tile_resources)
    {
        in_Node->AddResource(tile_resource);   
    }
}