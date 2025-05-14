#pragma once
#include "building.h"
#include "player.h"
class City : public Building
{
private:
    static int city_count;
    static const std::map<Resource,int> Cost;
public:
    City(Player*);
    
    void inc_building_count() override;
    void take_building_piece(Player*) override;
    void take_building_resource(Player*) override;


    int GetVictoryPoints() const override;
    int ProduceResourceCount() const override;
    Building::BuildingTypes GetBuildingType() const override;

    static const std::map<Resource,int> GetCost();
};

