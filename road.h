#pragma once
#include "building.h"
class Road : public Building
{
private:
    static int road_count;
public:
    Road();
    
    //1/3 a virtualis osztalynak elbaszott
    int GetVictoryPoints() const override;
};