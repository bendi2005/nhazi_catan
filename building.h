#pragma once
#include "magic_const.h"
#include <map>
#include <utility>
class Building   
{
private:
    
public:
    
    //ha keves a hely o megy elsonek
    virtual ~Building() = default;
    enum class BuildingTypes {EMPTY,SETTLEMENT, CITY, ROAD};
    

    virtual int GetVictoryPoints() const = 0;
    static BuildingTypes GetTypeFromChar(char);
    
    
};