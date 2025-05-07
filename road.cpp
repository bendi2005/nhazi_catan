#include "road.h"
int Road::road_count = 0;

const std::map<Resource,int> Road::Cost = {{BRICK,1},{LUMBER,1}};
Road::Road()
{
    road_count++;
}
int Road::GetVictoryPoints() const 
{
    return 0;
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

