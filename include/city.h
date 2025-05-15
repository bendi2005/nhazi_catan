#pragma once
#include "building.h"
#include "player.h"

//City is a type of Building
class City : public Building
{
private:
    //The number of cities on the board
    static int city_count;
    //The cost it takes to build a City, the maps: <What kind of Resource , How much>
    static const std::map<Resource,int> Cost;
public:
    //Increases the count of cities, gives back the player the settlement piece, takes a City piece, and takes the resources the City costs
    //OTC Constructor
    City(Player*);
    
    
    //Increases the number of cities
    void inc_building_count() override;
    //Takes a city piece from the Player and gives back the Settlement piece
    void take_building_piece(Player*) override;
    //Takes the resources needed for a city from the Player
    void take_building_resource(Player*) override;

    //Give VICTORY_POINT_VALUE_CITY number of vicotry point
    int GetVictoryPoints() const override;
    //Produces PRODUCE_RESOURCE_VALUE_CITY number of resources when next to rolled tile
    int ProduceResourceCount() const override;
    //Returns the Buildingtypes enum value of CITY
    Building::BuildingTypes GetBuildingType() const override;

    //Returns the cost of the city in a map: <What kind of Resource , How much>
    static const std::map<Resource,int> GetCost();
};

