#pragma once
#include "magic_const.h"
#include <map>
#include <utility>

class Player;
class Building   
{
private:
    
public:
    //Used to pass around in EventManager to make switch cases work
    enum BuildingTypes {SETTLEMENT, CITY, ROAD,EMPTY};
    
    //Pure virtual nature
    virtual ~Building() = default;

    //Increases the count of the certain building on the board (in this class its pure virtual)
    virtual void inc_building_count() = 0;
    //Takes a certain building piece from the player who builds it
    virtual void take_building_piece(Player*) = 0;
    //Takes the cost (=the resource card(s)) of the certain building from the player tha builds it
    virtual void take_building_resource(Player*) = 0;
    
    
    //At the end of the turn, give a certain number of victory points
    virtual int GetVictoryPoints() const = 0;
    
    //When the tile next to the certain buildining is rolled, distribute this many resources
    virtual int ProduceResourceCount() const = 0;

    //Returns the enum BuildingTypes value of current Building
    virtual Building::BuildingTypes GetBuildingType() const = 0;

    //Returns the enum BuildingTypes value from a lowercase char: corresponding to the first letter 
    static BuildingTypes GetTypeFromChar(char);
    
    
};