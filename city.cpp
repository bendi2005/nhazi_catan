#include "city.h"
int City::city_count = 0;

City::City()
{
    city_count++;
}

int City::GetVictoryPoints() const 
{
    return VICTORY_POINT_VALUE_CITY;
}
