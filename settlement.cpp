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

const std::map<Resource,int> Settlement::GetCost()
{
    return Settlement::Cost;
}


//std::map<Resource,int> Settlement::GetCost() const 
//{
//    std::map<Resource,int> retmap;
//    
//    retmap.insert(std::make_pair(Resource(BRICK),1));
//    retmap.insert(std::make_pair(Resource(LUMBER),1));
//    retmap.insert(std::make_pair(Resource(WOOL),1));
//    retmap.insert(std::make_pair(Resource(GRAIN),1));
//
//    return retmap;
//}
