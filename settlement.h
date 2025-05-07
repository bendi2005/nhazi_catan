#pragma once
#include "building.h"
class Settlement : public Building
{
private:
    //debugging
    static int settlement_count;
public:
    Settlement();
    int GetVictoryPoints() const override;
    
    static const std::map<Resource,int> Cost;
    static const std::map<Resource,int> GetCost();
};