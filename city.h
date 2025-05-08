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
    
    static const std::map<Resource,int> GetCost();
};

