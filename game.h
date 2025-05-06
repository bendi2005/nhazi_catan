#pragma once
#include "gameboard.h"
class Game
{
public:
    //OTC Constructor
    Game();


    //useful for debugging
    template<typename T> void PrintMap(std::map<Coordinate,T> in_map)
    {
        int i = 1;
        for(auto iter = in_map.begin();iter != in_map.end();iter++)
        {
            printf("Placeholder");
        }
        return;
    }
};