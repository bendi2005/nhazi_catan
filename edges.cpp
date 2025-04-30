#include "edges.h"
Coordinate Edge::GetPos() const 
{
    return edge_pos;
}
Edge::Edge()
{
    printf("gecigecigeci");
}
Edge::Edge(Coordinate c1,Coordinate c2)
{
    edge_pos = (c1+c2)/2;
}
