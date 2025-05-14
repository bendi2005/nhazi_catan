#pragma once
#include "game.h"
#include <string>
#include <stdio.h>

#include "settlement.h"
#include "city.h"
#include "road.h"



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

static void ClearNextId();
static int next_player_id;
//OTC Constructor
Player(std::string);


//Getters for owned things

std::vector<Node*> GetOwnedNodes(GameBoard*);
std::vector<Edge*> GetOwnedEdges(GameBoard*);



void AddResourceCard(int,ResourceTypes);



//Actions
void FirstTurnSet(GameBoard*);

void FirstTurnRoad(GameBoard*);

bool CanAfford(std::map<Resource,int>);







//ezekbol lehet semmi nem lesz lol
void RollDice(GameBoard*);
//aki eros itt meghivja a gameboard distribut fuggvenyet

void Trade(GameBoard*);
//na ezen majd gondolkozunk meg

void Build(GameBoard*);
//jo itt is majd lesz valami



//for std::map
bool operator<(const Player&);

};