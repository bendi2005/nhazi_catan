#pragma once
#include "coord.h"
#include "magic_const.h"
#include <string>



class Node;
class GameBoard;
class Tile
{
public:
static std::vector<Coordinate> NodePos;
static std::vector<Coordinate> EdgePos;
std::set<char> tile_resources; //nyilvan nem char hanem majd
Coordinate cords;
GameBoard* p_GB;
Tile(GameBoard*,Coordinate,std::set<char> = {'a'}); //nyilvan nem char
void GenerateNodes(GameBoard*);
void GenerateEdges(GameBoard*);
void PutResourcesIntoNode(Node*);
//TODO puresourcesintotile

};