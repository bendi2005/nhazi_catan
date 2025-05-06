#include "tiles.h"
#include "gameboard.h"
std::vector<Coordinate> Tile::NodePos = {Coordinate(-2,-2),Coordinate(-2,0),Coordinate(0,2),Coordinate(2,2),Coordinate(2,0 ),Coordinate(0,-2)};
std::vector<Coordinate> Tile::EdgePos = {Coordinate(-2,-1),Coordinate(-1,1),Coordinate(1,2),Coordinate(2,1),Coordinate(1,-1),Coordinate(-1,2)};
Tile::Tile(GameBoard* in_p_GB, Coordinate in_center,const std::set<Resource>& in_resource,int in_dicenum) : pos(in_center), p_GB(in_p_GB), dicenum(in_dicenum)
{
    
    //fills tile_resource_types
    for(const auto in_resource_element : in_resource)
    {
        AddResourceToTile(in_resource_element);
    }
    GenerateNodes(p_GB);

}



void Tile::AddResourceToTile(const Resource in_rsc)
{
    tile_resource_types.insert(in_rsc);
    return;
}

const std::set<Resource>& Tile::GetResourcesFromTile() const
{
    return tile_resource_types;
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
            it->second->AddTileToNode(this);   
        } 
        //not contain
        else {
            //Create it and add it to GameBoard
            //note2: This could be one line, but this execution follows the philosophy
            //of only calling constructors when they are guaranteed to not throw an error
            Node* N = new Node(cur,in_p_GB);
            N->AddTileToNode(this);
            std::pair<Coordinate,Node*> cur_node_pair_toadd = std::make_pair(cur,N);
            in_p_GB->Add_to_nodemap(cur_node_pair_toadd);
        }
    }   
}

const int Tile::GetDiceNum() const
{
    return dicenum;
}
