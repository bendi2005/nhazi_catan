#pragma once
class Coordinate
{
public: //TODO mi public mi privat
    int x;
    int y;
    Coordinate(int,int);
    Coordinate();
    bool Coordinate::operator!=(const Coordinate&) const;
    void GoRight();
    Coordinate BigToSmall(); 
    // void SmallToBig(); Ilyen nem kene elv
    Coordinate operator+(const Coordinate&);
    bool operator==(const Coordinate&) const;
};