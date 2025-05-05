#pragma once
#include "coord.h"
#include "magic_const.h"

#include "resource.h"
#include "nodes.h"

//necessary forward declaration
class GameBoard;

class Tile
{

private:

    //Offset vectors (math)
    static std::vector<Coordinate> NodePos;
    static std::vector<Coordinate> EdgePos;

    //trivial
    std::set<Resource> tile_resource_types; 
    Coordinate pos;
    GameBoard* p_GB;

    //For Nodes
    void GenerateNodes(GameBoard*);
    void PutResourcesIntoNode(Node*);
 
public:
    
    //OTC Constructor
    Tile(GameBoard*,Coordinate,const std::set<Resource>& = {});
    
    void AddResourceToTile(const Resource);
    const std::set<Resource>& GetResourcesFromTile() const;
    
    
};