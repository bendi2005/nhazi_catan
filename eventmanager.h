#pragma once
#include "game.h"
#include "player.h"
#include <vector>
class EventManager
{
private:
std::vector<Player*> vec_players;
int player_count;
int max_turncount;
GameBoard* GB = nullptr;

//lasd cpp
//enum enum_Actions 
//{
//    ROLL,BUILD,TRADE
//}; 
public:

//debug only
EventManager();


//OTC Constructor
EventManager(GameBoard*,int = 2,int = 10);


void InitPlayers(int);
const Player* SimGame();

};