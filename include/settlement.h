#pragma once
#include "building.h"
#include "player.h"

//Settlement is a type of Building
class Settlement : public Building
{
private:
    //The number of Settlements on the board
    static int settlement_count;
    //The cost it takes to build a Settlement, the maps: <What kind of Resource , How much>
    static const std::map<Resource,int> Cost;
public:

    //Increases the count of Settlements, takes a Settlement piece, and takes the resources the Settlement costs
    //OTC Constructor
    Settlement(Player*);

    //Increases the number of Settlements
    void inc_building_count() override;
    //Takes a Settlement piece from the Player 
    void take_building_piece(Player*) override;
    //Takes the resources needed for a Settlement from the Player
    void take_building_resource(Player*) override;

    //Gives VICTORY_POINT_VALUE_SETTLEMENT number of victory points
    int GetVictoryPoints() const override;
    //Produces PRODUCE_RESOURCE_VALUE_SETTLEMENT number of resources when next to rolled tile
    int ProduceResourceCount() const override;
    //Returns the Buildingtypes enum value of SETTLEMENT
    Building::BuildingTypes GetBuildingType() const override;

    //Returns the cost of the Settlement in a map: <What kind of Resource , How much>
    static const std::map<Resource,int> GetCost();


};

