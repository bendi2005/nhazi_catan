#pragma once 

#include "resource.h"
class Coordinate
{    
private:
    
public: 
//TODO mi public mi privat
    Coordinate();   
    int x;
    int y;
    Coordinate(int,int);

    bool operator!=(const Coordinate&) const;
    Coordinate BigToSmall(); 
    
    bool operator==(const Coordinate&) const;
    bool operator<(const Coordinate&) const;
    Coordinate operator/(int) const;
    void PrintCord() const;
    //operator>(const Coordinate&) const;
};
Coordinate operator+(const Coordinate&,const Coordinate&);