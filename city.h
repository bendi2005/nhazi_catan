#pragma once
#include "building.h"
class City : public Building
{
private:
    static int city_count;
    static const std::map<Resource,int> Cost;
public:
    City();
    
    int GetVictoryPoints() const override;
    int ProduceResource() const override;
    Building::BuildingTypes GetBuildingType() const override;

    static const std::map<Resource,int> GetCost();
};

