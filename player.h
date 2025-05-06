#pragma once
#include "game.h"
#include <string>
#include <stdio.h>
class Player
{
private:
    
    int id;
    std::string player_name;

public:

static int next_id;
//OTC Constructor
Player(std::string);


//Actions
void FirstTurnSet(GameBoard*);

void FirstTurnRoad(GameBoard*);

void RollDice(GameBoard*);
//aki eros itt meghivja a gameboard distribut fuggvenyet

void Trade(GameBoard*);
//na ezen majd gondolkozunk meg

void Build(GameBoard*);
//jo itt is majd lesz valami

//static void ClearNextId();
bool operator<(const Player&);

};