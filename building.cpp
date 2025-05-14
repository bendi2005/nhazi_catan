#include "building.h"
Building::BuildingTypes Building::GetTypeFromChar(char c)
{
    switch(c)
    {
        case 's' :
            return Building::BuildingTypes::SETTLEMENT;
        case 'c' : 
            return Building::BuildingTypes::CITY;
        case 'r' :
            return Building::BuildingTypes::ROAD;
        default :
            return Building::BuildingTypes::EMPTY;
    }
}


