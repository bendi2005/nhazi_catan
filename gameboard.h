#pragma once
#include "coord.h"
#include "magic_const.h"

#include "nodes.h"
#include "edges.h"
#include "tiles.h"
#include <time.h>

#include "player.h"
#include "building.h"


#include <vector> 
#include <map>
#include <utility> //#include <map> might not include std::make_pair

class GameBoard 
{
private:
    //Handles which element of resource_types_for_tiles vector is the next tile's
    static int rstpindex;

    //Maps of Node,Edge,Tile
    std::map<Coordinate,Node*> nodemap;
    std::map<Coordinate,Edge*> edgemap;
    std::map<Coordinate,Tile*> tilemap;

    
    //Passes in the resource_type to to tile
    std::vector<std::set<Resource>> resource_types_for_tiles;
   
    //Need this for CalcEnd();
    inline int min(int a,int b)
    {
        return (a > b) ? b : a;
    }    
    
    //Calculate functions:
    
    //Calculates the coordinate of the tile it needs to END generating the in_line_num-th line 
    Coordinate CalcBegin(int);
    //Calculates the coordinate of the tile it needs to END generating the in_line_num-th line 
    Coordinate CalcEnd(int);

    void GenerateLine(int);
public:   //TODO mi privat mi publikus


    int Get_rstpindex() const;
    void Set_rstpindex(const int);

    const std::map<Coordinate,Node*>& Get_nodemap() const;
    void Add_to_nodemap(const std::pair<Coordinate,Node*>);

    const std::map<Coordinate,Edge*>& Get_edgemap() const;
    void Add_to_edgemap(const std::pair<Coordinate,Edge*>);

    const std::map<Coordinate,Tile*>& Get_tilemap() const;
    void Add_to_tilemap(const std::pair<Coordinate,Tile*>);

    //OTC Constructor
    GameBoard(std::vector<std::set<Resource>> = 
        {{WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL},
        {WOOL}
        
        }); 

    //felig teszt    
    void PrintHarbor() const;
};



