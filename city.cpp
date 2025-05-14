#include "city.h"
const std::map<Resource,int> City::Cost = {{ORE,3},{GRAIN,2}};
int City::city_count = 0;

City::City()
{
    city_count++;
}

int City::GetVictoryPoints() const 
{
    return VICTORY_POINT_VALUE_CITY;
}

int City::ProduceResource() const 
{
    return PRODUCE_RESOURCE_VALUE_CITY;
}

Building::BuildingTypes City::GetBuildingType() const
{
    return Building::BuildingTypes::CITY;
}

const std::map<Resource,int> City::GetCost()
{
    return City::Cost;
}

//std::map<Resource,int> City::GetCost() const 
//{
//    std::map<Resource,int> retmap;
//    
//    retmap.insert(std::make_pair(Resource(ORE),3));
//    retmap.insert(std::make_pair(Resource(GRAIN),2));
//
//    return retmap;  
//}
