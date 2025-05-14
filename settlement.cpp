#include "settlement.h"
int Settlement::settlement_count = 0;

const std::map<Resource,int> Settlement::Cost = {{BRICK,1},{LUMBER,1},{WOOL,1},{GRAIN,1}};
Settlement::Settlement()
{
    //also for debugging (same thing)
    settlement_count++;
}
int Settlement::GetVictoryPoints() const 
{
    return VICTORY_POINT_VALUE_SETTLEMENT;
}

int Settlement::ProduceResource() const
{
    return PRODUCE_RESOURCE_VALUE_SETTLEMENT;
}


const std::map<Resource,int> Settlement::GetCost()
{
    return Settlement::Cost;
}

Building::BuildingTypes Settlement::GetBuildingType() const 
{
    return BuildingTypes::SETTLEMENT;
}

