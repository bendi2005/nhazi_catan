#include "../include/coord.h"
#include <stdio.h>

Coordinate::Coordinate(int in_x,int in_y) : x(in_x), y(in_y) {}

sf::Vector2f Coordinate::OrtoPos()
{
   
    float ex = TILE_SIDELENGHT* y *1.73205f/4;
    float why = TILE_SIDELENGHT * (x/2.0 - y/4.0);

    return sf::Vector2f{ex,why};
}

sf::Vector2f Coordinate::ScaledOrtoPos(float scale)
{   
    sf::Vector2f postoscale = OrtoPos();
    return sf::Vector2f{postoscale.x*scale,postoscale.y*scale};
}

sf::Vector2f Coordinate::ScaledOrtoOrigoOffsetPos(float scale)
{
    sf::Vector2f postooffset = ScaledOrtoPos(scale);    
    return sf::Vector2f{postooffset.x+ORIGO.x,postooffset.y+ORIGO.y};
}



bool Coordinate::operator!=(const Coordinate& other) const
{
    return ((this->x != other.x ) || (this->y != other.y));
}
Coordinate Coordinate::BigToSmall()
{
    Coordinate ret_c((2 * x + 2 * y),(-2 * x + 4 * y));
    return ret_c;
}

Coordinate operator+(const Coordinate& first,const Coordinate& second)
{
    return Coordinate(first.x+second.x,first.y+second.y);
}

bool Coordinate::operator==(const Coordinate& other) const
{
    return ((this->x==other.x) && (this->y == other.y));
}

bool Coordinate::operator<(const Coordinate& other) const 
{
    return (x < other.x) || ((x == other.x) && (y<other.y));
    
}

Coordinate Coordinate::operator/(int divisor) const
{
    return Coordinate(x/divisor,y/divisor);
}

void Coordinate::PrintCord() const
{
    printf("\n%d  %d\n",x,y);
}


int Coordinate::GetX() const 
{
    return x;
}


int Coordinate::GetY() const 
{
    return y;
}





