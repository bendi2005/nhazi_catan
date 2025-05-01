#pragma once
#include "coord.h"
#include "magic_const.h"

#include "resource.h"
#include "nodes.h"


class GameBoard;
class Tile
{
public:

static std::vector<Coordinate> NodePos;
static std::vector<Coordinate> EdgePos;

int id;

std::set<Resource> tile_resource_types; //nyilvan nem char hanem majd
Coordinate pos;
GameBoard* p_GB;
Tile(GameBoard*,Coordinate,const std::set<Resource>* = nullptr); //nyilvan nem char

void GenerateNodes(GameBoard*);
//void GenerateEdges(GameBoard*);
void PutResourcesIntoNode(Node*);
//TODO puresourcesintotile

};