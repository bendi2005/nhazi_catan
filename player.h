#pragma once
#include "game.h"
#include <string>
#include <stdio.h>

struct Inventory
{
    int settlements_available;
    int cities_available;
    int roads_available;
    std::map<Resource,int> resource_cards;
};

class Player
{
private:
    
    int player_id;
    std::string player_name;
    Inventory inventory;

public:

static int next_player_id;
//OTC Constructor
Player(std::string);


//Actions
void FirstTurnSet(GameBoard*);

void FirstTurnRoad(GameBoard*);

bool CanAfford(Building);


void RollDice(GameBoard*);
//aki eros itt meghivja a gameboard distribut fuggvenyet

void Trade(GameBoard*);
//na ezen majd gondolkozunk meg

void Build(GameBoard*);
//jo itt is majd lesz valami

//static void ClearNextId();
bool operator<(const Player&);

};