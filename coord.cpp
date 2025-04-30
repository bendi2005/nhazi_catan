#include "coord.h"
#include <stdio.h>
Coordinate::Coordinate()
{
    printf("coord def constr called (nem kene)");
}
Coordinate::Coordinate(int in_x,int in_y) : x(in_x), y(in_y) {}

bool Coordinate::operator!=(const Coordinate& other) const
{
    return ((this->x != other.x ) || (this->y != other.y));
}
void Coordinate::GoRight()
{
    this->y++;
}

Coordinate Coordinate::BigToSmall()
{
    
    Coordinate ret_c((2 * x + 2 * y),(-2 * x + 4 * y));
    ret_c.PrintCord();
    return ret_c;
}

Coordinate Coordinate::operator+(const Coordinate& other)
{
    this->x+=other.x;
    this->y+=other.y;
    return *this;
}
bool Coordinate::operator==(const Coordinate& other) const
{
    return ((this->x==other.x) && (this->y == other.y));
}
bool Coordinate::operator<(const Coordinate& other) const 
{
    return (this->x < other.x);
}
Coordinate Coordinate::operator/(int divisor) const
{
    return Coordinate(x/divisor,y/divisor);
}
void Coordinate::PrintCord() const
{
    printf("\n%d  %d\n",x,y);
}