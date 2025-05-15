#pragma once
#include "building.h"
#include "player.h"

//City is a type of Building
class Road : public Building
{
private:
    //The number of Roads on the board    
    static int road_count;
    //The cost it takes to build a Road, the maps: <What kind of Resource , How much>
    static const std::map<Resource,int> Cost;
public:
    //Increases the count of Roads, takes a Road piece, and takes the resources the Road costs
    //OTC Constructor
    Road(Player*);

    //Increases the number of Roads
    void inc_building_count() override;
    //Takes a Road piece from the Player 
    void take_building_piece(Player*) override;
    //Takes the resources needed for a Road from the Player
    void take_building_resource(Player*) override;

        
    //Give VICTORY_POINT_VALUE_ROAD number of vicotry points
    int GetVictoryPoints() const override;
    //Produces PRODUCE_RESOURCE_VALUE_ROAD number of resources when next to rolled tile
    int ProduceResourceCount() const override;
    
    //Returns the Buildingtypes enum value of ROAD
    Building::BuildingTypes GetBuildingType() const override;

    //Returns the cost of the ROAD in a map: <What kind of Resource , How much>
    static const std::map<Resource,int> GetCost();
};