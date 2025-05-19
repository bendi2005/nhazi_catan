#include "../include/road.h"
int Road::road_count = 0;

const std::map<Resource,int> Road::Cost = {{ResourceTypes::BRICK,1},{ResourceTypes::LUMBER,1}};

Road::Road(Player* in_player)
{
    inc_building_count();
    take_building_piece(in_player);
    take_building_resource(in_player);
    printf("Road built by: %s\n",in_player->GetName().c_str());
}

void Road::take_building_piece(Player* in_player)
{
    in_player->TakeRoadPiece();
}

void Road::inc_building_count()
{
    road_count++;
}

void Road::take_building_resource(Player* in_player)
{
    in_player->TakeBuildingResources(Cost);
}



int Road::GetVictoryPoints() const 
{
    return VICTORY_POINT_VALUE_ROAD;
}

int Road::ProduceResourceCount() const 
{
    return PRODUCE_RESOURCE_VALUE_ROAD;
}

Building::BuildingTypes Road::GetBuildingType() const
{
    return Building::BuildingTypes::ROAD;
}


const std::map<Resource,int> Road::GetCost()
{
    return Road::Cost;
}

//std::map<Resource,int> Road::GetCost() const 
//{
//    std::map<Resource,int> retmap;
//    
//    retmap.insert(std::make_pair(Resource(BRICK),1));
//    retmap.insert(std::make_pair(Resource(LUMBER),1));
//
//    return retmap;
//}

