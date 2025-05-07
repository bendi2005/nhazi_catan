#include "settlement.h"
int Settlement::settlement_count = 0;
Settlement::Settlement()
{
    settlement_count++;
}
int Settlement::GetVictoryPoints() const 
{
    return VICTORY_POINT_VALUE_SETTLEMENT;
}