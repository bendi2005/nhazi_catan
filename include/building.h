#pragma once
#include "magic_const.h"
#include <map>
#include <utility>

class Player;
class Building   
{
private:
    
public:
    enum class BuildingTypes {EMPTY,SETTLEMENT, CITY, ROAD};
    
    virtual ~Building() = default;
    virtual void inc_building_count() = 0;
    virtual void take_building_piece(Player*) = 0;
    virtual void take_building_resource(Player*) = 0;
    
    
    virtual int GetVictoryPoints() const = 0;
    virtual int ProduceResourceCount() const = 0;
    virtual Building::BuildingTypes GetBuildingType() const = 0;

    static BuildingTypes GetTypeFromChar(char);
    
    
};