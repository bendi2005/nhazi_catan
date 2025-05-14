#include "settlement.h"
int Settlement::settlement_count = 0;

const std::map<Resource,int> Settlement::Cost = {{BRICK,1},{LUMBER,1},{WOOL,1},{GRAIN,1}};


Settlement::Settlement(Player* in_player)
{
    inc_building_count();
    take_building_piece(in_player);
    take_building_resource(in_player);
}

void Settlement::inc_building_count()
{
    settlement_count++;
}

void Settlement::take_building_piece(Player* in_player)
{
    in_player->TakeSettlementPiece();
}

void Settlement::take_building_resource(Player* in_player)
{
    in_player->TakeBuildingResources(Cost);
}



void Settlement::DestructSettlement(Player* in_player)
{
    in_player->GiveBackSettlementPiece();
    settlement_count--;
}

int Settlement::GetVictoryPoints() const 
{
    return VICTORY_POINT_VALUE_SETTLEMENT;
}

int Settlement::ProduceResourceCount() const
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

