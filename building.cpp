#include "building.h"
Building::BuildingTypes Building::GetTypeFromChar(char c)
{
    switch(c)
    {
        case 's' :
            return Building::BuildingTypes::SETTLEMENT;
            break;
        case 'c' : 
            return Building::BuildingTypes::CITY;
            break;
        case 'r' :
            return Building::BuildingTypes::ROAD;
            break;
        default :
            return Building::BuildingTypes::EMPTY;
    }
}


