#pragma once
#include "building.h"
class Road : public Building
{
private:
    //for debug
    static int road_count;
    static const std::map<Resource,int> Cost;
public:
    Road();
    
    int GetVictoryPoints() const override;
    
    int ProduceResource() const override;
    
    Building::BuildingTypes GetBuildingType() const override;

    static const std::map<Resource,int> GetCost();
};