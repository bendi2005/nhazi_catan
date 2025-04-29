#include "tiles.h"
#include "gameboard.h"
std::vector<Coordinate> Tile::EdgePos = {Coordinate(-2,-1),Coordinate(-1,1),Coordinate(1,2),Coordinate(2,1),Coordinate(1,-1),Coordinate(-1,2)};
std::vector<Coordinate> Tile::NodePos = {Coordinate(-2,-2),Coordinate(-2,0),Coordinate(0,2),Coordinate(2,2),Coordinate(2,0 ),Coordinate(0,-2)};
Tile::Tile(GameBoard* in_p_GB, Coordinate in_center,char in_resource) : cords(in_center)
{
    p_GB = in_p_GB;
    //ha esetleg megis vektor kene (nem fog)
    //tile_resources.reserve(HOW_MANY_RESOURCE_DOES_A_TILE_HAVE);
    tile_resources.insert(in_resource);
    GenerateNodes(in_p_GB);

}
void Tile::GenerateNodes(GameBoard* in_p_GB)
{
    auto& n_map = in_p_GB->nodemap;
    
    for(int i = 0;i<SIDE_LENGHT;i++)
    {
        //current node coord
        Coordinate cur = EdgePos[i];
        
        //check if map contains current node
        auto it = n_map.find(cur);
        
        //contain
        if(it != n_map.end())
        {
            //ember bazdmeg hogy nez ez ki
            PutResourcesIntoNode(*(*it).second);
            
        } 
        //not contain
        else {
            Node* N = new Node(cur,i,in_p_GB); //constructor explained in nodes.h
            PutResourcesIntoNode(*N);
            n_map.insert(std::make_pair(cur,N));
        }
    }   
}
void Tile::PutResourcesIntoNode(Node& in_Node)
{
    for(const auto& tile_resource : tile_resources)
    {
        in_Node.AddResource(tile_resource);   
    }
}