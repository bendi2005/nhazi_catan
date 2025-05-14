#pragma once
#include "building.h"
#include "player.h"
class Road : public Building
{
private:
    //for debug
    static int road_count;
    static const std::map<Resource,int> Cost;
public:
    Road(Player*);

    void inc_building_count() override;
    void take_building_piece(Player*) override;
    void take_building_resource(Player*) override;

        
    
    int GetVictoryPoints() const override;
    
    int ProduceResourceCount() const override;
    
    Building::BuildingTypes GetBuildingType() const override;

    static const std::map<Resource,int> GetCost();
};