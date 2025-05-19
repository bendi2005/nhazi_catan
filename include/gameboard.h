#pragma once
#include "coord.h"
#include "magic_const.h"


#include "edges.h"
#include "tiles.h" //contains nodes.h
#include <time.h>

#include "player.h"
#include "building.h"


#include <vector> 
#include <map>
#include <utility> //#include <map> might not include std::make_pair


class Edge;
class Node;
class Tile;


class GameBoard 
{
private:
    
    
    //Handles which element of resource_types_for_tiles vector is the next tile's
    static int rstpindex;
    //Same as ^ but for die num
    static int dienumindex;

    
    //Map of Node's on the GameBoard
    std::map<Coordinate,Node*> nodemap;
    //Map of Edge's on the GameBoard
    std::map<Coordinate,Edge*> edgemap;
    //Map of Tile's on the GameBoard
    std::map<Coordinate,Tile*> tilemap;

    std::vector<sf::CircleShape> tile_images;
    std::vector<sf::CircleShape> node_images;
    std::vector<sf::CircleShape> edge_images;



    //vector of sets of Resources for each tile: the nth (0-indexed) set is the set of resources for the nth tile
    std::vector<std::set<Resource>> resource_types_for_tiles;
    //vector of the Diece numbers for each tile: the nth (0-indexed) int is the die number for the nth tile
    std::vector<int> dicenum_for_tiles;


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


    //Generates a line of tiles
    void GenerateLine(int);


//Function pointers to functions handling checking the criteria to building and building
//Need to define these before vectors of them
public:
    //Criterion function, only depending on the state of the board
    using CritFunction = bool(GameBoard::*)(Coordinate, Player*) const;
    //Building function
    using BuildFunction = void(GameBoard::*)(Coordinate, Player*,Building::BuildingTypes);
private:
    
    std::vector<CritFunction> SettlementCriteria;
    std::vector<CritFunction> CityCriteria ;
    std::vector<CritFunction> RoadCriteria;
    std::vector<CritFunction> FirstTurnSettlementCriteria;
    


    //BuildFunctions
    BuildFunction BuildSettlement;
    BuildFunction UpgradeSettlement;
    BuildFunction BuildRoad;


public:   //TODO mi privat mi publikus


    void InitFuncStuff();
    
    //Getters for CritFunctions
    const std::vector<GameBoard::CritFunction>& GetSettlementCriteriaFunction() const;
    const std::vector<GameBoard::CritFunction>& GetCityCriteriaFunction() const;
    const std::vector<GameBoard::CritFunction>& GetRoadCriteriaFunction() const;
    const std::vector<CritFunction>& GetFirstTurnSettlementCriteria() const;


    //Getters for BuildFunctions
    BuildFunction GetSettlementBuildFunction() const;    
    BuildFunction GetUpgradeSettlementFunction() const;
    BuildFunction GetRoadBuildFunction() const;


    //Getter and Setter for rstpindex
    int Get_rstpindex() const;
    void Set_rstpindex(const int);


    //Getters and Setters for maps

    const std::map<Coordinate,Node*>& Get_nodemap() const;
    void Add_to_nodemap(const std::pair<Coordinate,Node*>);

    const std::map<Coordinate,Edge*>& Get_edgemap() const;
    void Add_to_edgemap(const std::pair<Coordinate,Edge*>);

    const std::map<Coordinate,Tile*>& Get_tilemap() const;
    void Add_to_tilemap(const std::pair<Coordinate,Tile*>);

    //const std::vector<sf::CircleShape>& Get_TileImages() const;
    //void Add_to_tileimages(const sf::CircleShape);
//
    //const std::vector<sf::CircleShape>& Get_NodeImages() const;
    //void Add_to_nodeimages(const sf::CircleShape);
//
    //const std::vector<sf::CircleShape>& Get_EdgeImages() const;
    //void Add_to_edgeimages(const sf::CircleShape);

    void DrawTiles(std::vector<sf::CircleShape>*);
    
    void DrawEdges(std::vector<sf::RectangleShape>*);

    void DrawNodes(std::vector<sf::CircleShape>*);

    void BuildSettlementFunction(Coordinate,Player*,Building::BuildingTypes);
    void UpgradeSettlementFunction(Coordinate, Player*,Building::BuildingTypes);
    void BuildRoadFunction(Coordinate,Player*,Building::BuildingTypes);
    
        
    //Criteria Functions

    //Node 
    bool Crit_isFreeNode(Coordinate,Player*)const;
    bool Crit_Distance(Coordinate,Player*)const;
    bool Crit_Node_Connected(Coordinate,Player*)const;
    
    //Edge
    bool Crit_isFreeEdge(Coordinate,Player*)const;
    bool Crit_Edge_Connected(Coordinate,Player*) const;
    
    //City
    bool Crit_isNodeUpgradeAble(Coordinate,Player*) const;

    
    
    int SettlementInRadius(const sf::Vector2i);
    
    int RoadInRadius(const sf::Vector2i);
    

    //OTC Constructor
    GameBoard(std::vector<std::set<Resource>> = {{ResourceTypes::ORE}, {ResourceTypes::WOOL}, {ResourceTypes::LUMBER}, {ResourceTypes::GRAIN}, {ResourceTypes::BRICK}, {ResourceTypes::WOOL}, {ResourceTypes::BRICK}, {ResourceTypes::GRAIN}, {ResourceTypes::LUMBER}, {ResourceTypes::DESERT}, {ResourceTypes::LUMBER}, {ResourceTypes::ORE}, {ResourceTypes::LUMBER}, {ResourceTypes::ORE}, {ResourceTypes::GRAIN}, {ResourceTypes::WOOL}, {ResourceTypes::BRICK}, {ResourceTypes::GRAIN}, {ResourceTypes::WOOL}},std::vector<int> ={10,2,9,12,6,4,10,9,11,7,3,8,8,3,4,5,5,6,11});

    //felig teszt    
    void PrintHarbor() const;


    //converter
    const Coordinate id_to_coord(int,Building::BuildingTypes) const;

    int RollDice() const;

    void DistributeResources();

};



