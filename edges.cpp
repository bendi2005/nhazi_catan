#include "edges.h"
const Coordinate Edge::GetPos() const 
{
    return Coordinate(((node_1_pos.x+node_2_pos.x)/2),(node_1_pos.y+node_2_pos.y)/2);
}
Edge::Edge()
{
    printf("nem kene");
}
Edge::Edge(const Coordinate& c1,const Coordinate& c2) : node_1_pos(c1),node_2_pos(c2)
{

}
