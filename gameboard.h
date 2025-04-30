#pragma once
#include "coord.h"
#include "nodes.h"
#include "edges.h"
#include "tiles.h"
#include "magic_const.h"
#include <map>
#include <vector> //ezeket meg feltakaritjuk
#include <utility> //#include <map> might not include std::make_pair

class GameBoard 
{
public:   //TODO mi privat mi publikus

    //static std::vector<Coordinate> NodePos;
    //static std::vector<Coordinate> EdgePos;  //itt miert nem jo a const lol

    std::map<Coordinate,Node*> nodemap;
    std::map<Coordinate,Edge*> edgemap;
    std::map<Coordinate,Tile*> tilemap;

    static int rstpindex;

    std::vector<std::set<Resource>> resource_types_for_tiles;
    //TODO desc
    inline int min(int a,int b)
    {
        return (a > b) ? b : a;
    }    
    Coordinate CalcBegin(int);
    Coordinate CalcEnd(int);
    GameBoard(std::vector<std::set<Resource>> = {}); 
    void GenerateLine(int);



};