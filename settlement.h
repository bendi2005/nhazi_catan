#pragma once
#include "building.h"
#include "player.h"
class Settlement : public Building
{
private:
    //debugging
    static int settlement_count;
    static const std::map<Resource,int> Cost;
public:
    //OTC Constructor, decreases settlement pieces of player building
    Settlement(Player*);

    void inc_building_count() override;
    void take_building_piece(Player*) override;
    void take_building_resource(Player*) override;


    void DestructSettlement(Player*);

    

    

    int GetVictoryPoints() const override;
    int ProduceResourceCount() const override;
    Building::BuildingTypes GetBuildingType() const override;

    static const std::map<Resource,int> GetCost();


};

