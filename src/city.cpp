#include "../include/city.h"
const std::map<Resource,int> City::Cost = {{ResourceTypes::ORE,3},{ResourceTypes::GRAIN,2}};
int City::city_count = 0;

City::City(Player* in_player)
{
    inc_building_count();
    take_building_piece(in_player);
    take_building_resource(in_player);
}

void City::inc_building_count()
{
    city_count++;
}

//This is a special instance of this function: it also gives back the settlement piece
void City::take_building_piece(Player* in_player)
{
    in_player->GiveBackSettlementPiece();
    in_player->TakeCityPiece();
}

void City::take_building_resource(Player* in_player)
{
    in_player->TakeBuildingResources(Cost);
}




int City::GetVictoryPoints() const 
{
    return VICTORY_POINT_VALUE_CITY;
}

int City::ProduceResourceCount() const 
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
