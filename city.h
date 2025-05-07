#pragma once
#include "building.h"
class City : public Building
{
private:
    static int city_count;
public:
    City();
    int GetVictoryPoints() const override;
};