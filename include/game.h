#pragma once
#include "gameboard.h"
#include <map>
#include <utility>

class Game
{
public:
    //OTC Constructor
    Game();


    
    
    //useful for debugging
    template<typename T> void PrintMap(std::map<Coordinate,T> in_map)
    {
        int i = 0;
        for(auto iter = in_map.begin();iter != in_map.end();iter++)
        {
            printf("id: %d x: %d y: %d\n",iter->second->GetNodeId(),iter->first.GetX(),iter->first.GetY());
            i++;
        }
        printf("\nCount: %d\n",i);
        return;
    }
};