#pragma once 
#include "../SFML-3.0.0/include/SFML/Graphics.hpp"
#include "resource.h"
#include "magic_const.h"
class Coordinate
{    
private:
    
public: 
//TODO mi public mi privat
    //Shouldnt be called
    Coordinate() = delete;   
    
    //Unit directions
    int x;
    int y;
    
    //Sets x and y to the ints in the parameter list
    //OTC Constructor
    Coordinate(int,int);

    //For comparing if two Coordinates are the same (Returns false if both x and y are equal, else returns True)
    bool operator!=(const Coordinate&) const;

    //Changes Coordinate from the Tile-system (big) to Node+Edge system (small) (see dev_docs: Coordiante Systems)
    Coordinate BigToSmall(); 
    
    //For compaing if two Coordinates are the same (Returns true if both x and y are equal, else returns false)
    bool operator==(const Coordinate&) const;
    //Needed for making a map with Coordinates as keys, orders them by first x and second y value
    bool operator<(const Coordinate&) const;
    //Divides both x and y by the parameter int
    Coordinate operator/(int) const;
    //Prints out x and y in int form
    void PrintCord() const;

    //Getter for X
    int GetX() const;
    //Getter for Y
    int GetY() const;

    sf::Vector2f OrtoPos();
    
    sf::Vector2f ScaledOrtoOrigoOffsetPos();

    


};
//For adding two Coordinates together: adds x and y respectively
Coordinate operator+(const Coordinate&,const Coordinate&);

