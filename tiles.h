#pragma once
#include "coord.h"
#include "magic_const.h"

#include "resource.h"
#include "nodes.h"

//necessary forward declaration
class GameBoard;


class Player;
class Node;
class Tile
{

private:

    //Offset vectors (math)
    static std::vector<Coordinate> NodePos;
    static std::vector<Coordinate> EdgePos;

    //properties of Tile
    std::set<Resource> tile_resources; 
    Coordinate pos;
    GameBoard* p_GB;
    int dienum;

    //For Nodes
    void GenerateNodes(GameBoard*);
    void PutResourcesIntoNode(Node*);
 
public:
    
    //OTC Constructor
    Tile(GameBoard*,Coordinate,const std::set<Resource>& ,int);
    

    //Getter and Setter for resources of tile (Setter sets 1, Getter gets all)
    const std::set<Resource>& GetResourcesFromTile() const;
    void AddResourceToTile(const Resource);
    
    //Getter for DieNum
    int GetDieNum() const;
    
    void GiveResources(Player*,int) ;
    
};