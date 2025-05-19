#include "../include/tiles.h"
#include "../include/gameboard.h"
#include <iostream>

//set offsets
std::vector<Coordinate> Tile::NodePos = {Coordinate(-2,-2),Coordinate(-2,0),Coordinate(0,2),Coordinate(2,2),Coordinate(2,0 ),Coordinate(0,-2)};
std::vector<Coordinate> Tile::EdgePos = {Coordinate(-2,-1),Coordinate(-1,1),Coordinate(1,2),Coordinate(2,1),Coordinate(1,-1),Coordinate(-1,2)};
Tile::Tile(GameBoard* in_p_GB, Coordinate in_center,const std::set<Resource>& in_resource,int in_dienum) : pos(in_center), p_GB(in_p_GB), dienum(in_dienum)
{
    
    //fills tile_resources
    for(const auto in_resource_element : in_resource)
    {
        AddResourceToTile(in_resource_element);
    }

    //Generates nodes around current tile
    GenerateNodes(p_GB);

}

//Generates nodes around current tile
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

//Getter and Setter for resources of tile (Setter sets 1, Getter gets all)
void Tile::AddResourceToTile(const Resource in_rsc)
{
    tile_resources.insert(in_rsc);
    return;
}

const std::set<Resource>& Tile::GetResourcesFromTile() const
{
    return tile_resources;
} 

//Getter for DieNum

int Tile::GetDieNum() const
{
    return dienum;
}

void Tile::GiveResources(Player* in_player,int in_rcount) 
{
    for(auto rs : tile_resources)
    {
        if(rs.Resourcetype != ResourceTypes::DESERT)
        {
            in_player->AddResourceCard(in_rcount,rs);
        }

    }
    

}

sf::CircleShape Tile::MakeTileImage()
{
    sf::CircleShape ret_tile(TILE_RADIUS,SHAPE_NODE_COUNT);   
    ret_tile.setOrigin({TILE_RADIUS,TILE_RADIUS});
    ret_tile.setFillColor(ColorByResource());
    ret_tile.setPosition(pos.ScaledOrtoOrigoOffsetPos());
    //ret_tile.move({TILE_BULLSHIT_OFFSET_X,TILE_BULLSHIT_OFFSET_Y});
    return ret_tile;
}

sf::Color Tile::ColorByResource()
{
    if(tile_resources.size() == 1)
    {
        switch(tile_resources.begin()->Resourcetype)
        {
            case ResourceTypes::BRICK :
               
                return BRICK_COLOR;
            case ResourceTypes::LUMBER :
                return LUMBER_COLOR;
            case ResourceTypes::WOOL :
                return WOOL_COLOR;
            case ResourceTypes::GRAIN :
                return GRAIN_COLOR;
            case ResourceTypes::ORE :
                return ORE_COLOR;
            case ResourceTypes::DESERT :
                return DESERT_COLOR;
        }
    } else 
    {
        return MULTIRESOURCE_COLOR;
    }
}


