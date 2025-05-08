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


//de szep
public:
    using CritFunction = bool(GameBoard::*)(Coordinate, Player*) const;
    using BuildFunction = void(GameBoard::*)(Coordinate, Player*,Building::BuildingTypes);
private:
    const std::vector<CritFunction> SettlementCriteria;
    const std::vector<CritFunction> CityCriteria ;
    const std::vector<CritFunction> RoadCriteria;


    BuildFunction BuildSettlement;
    BuildFunction UpgradeSettlement;
    BuildFunction BuildRoad;


public:   //TODO mi privat mi publikus

    

    const std::vector<GameBoard::CritFunction>& GetSettlementCriteriaFunction() const;
    const std::vector<GameBoard::CritFunction>& GetCityCriteriaFunction() const;
    const std::vector<GameBoard::CritFunction>& GetRoadCriteriaFunction() const;
    
    BuildFunction GetSettlementBuildFunction() const;    
    BuildFunction GetUpgradeSettlementFunction() const;
    BuildFunction GetRoadBuildFunction() const;


    int Get_rstpindex() const;
    void Set_rstpindex(const int);

    const std::map<Coordinate,Node*>& Get_nodemap() const;
    void Add_to_nodemap(const std::pair<Coordinate,Node*>);

    const std::map<Coordinate,Edge*>& Get_edgemap() const;
    void Add_to_edgemap(const std::pair<Coordinate,Edge*>);

    const std::map<Coordinate,Tile*>& Get_tilemap() const;
    void Add_to_tilemap(const std::pair<Coordinate,Tile*>);


    void BuildSettlementFunction(Coordinate,Player*,Building::BuildingTypes);
    void UpgradeSettlementFunction(Coordinate, Player*,Building::BuildingTypes);
    void BuildRoadFunction(Coordinate,Player*,Building::BuildingTypes);
    
        
    
    
    
    
    //OTC Constructor
    GameBoard(std::vector<std::set<Resource>> = {{WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}, {WOOL}});

    //felig teszt    
    void PrintHarbor() const;


    //converter
    const Coordinate id_to_coord(int,Building::BuildingTypes) const;


    //Criterias  

    
    //NODE itt a Player* azert van mert kurvameno fuggvenypointer vektort
    //hasznalni

    //ezek trivialisak 
     bool Crit_isFreeNode( Coordinate, Player* )const;
    //getneighbour es mindegyik hitnek owner_node nullptr
     bool Crit_Distance( Coordinate, Player* )const;
    //TODO
     bool Crit_Node_Connected( Coordinate, Player* )const;
    
    

    //Edge
     bool Crit_isFreeEdge( Coordinate, Player* )const;
    //edge nodejai kozul valamelyik NEM nullptr (mindketto nem lehet elobbi miatt)
    //VAGY 
    //edge nodejai kozul valamelyiknek valamelyik edgenek ownerje NEM nullptr ()
     bool Crit_Edge_Connected( Coordinate, Player* ) const;
    

    //City
     bool Crit_isNodeUpgradeAble( Coordinate, Player* ) const;


    
    
    
    


    //Builds
    

};



