#pragma once 
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
    void GoRight();
    Coordinate BigToSmall(); 
    // void SmallToBig(); Ilyen nem     kene elv
    
    bool operator==(const Coordinate&) const;
    bool operator<(const Coordinate&) const;
    Coordinate operator/(int) const;
    void PrintCord() const;
    //operator>(const Coordinate&) const;
};
Coordinate operator+(const Coordinate&,const Coordinate&);