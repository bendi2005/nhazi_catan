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

//Called for idk what
static void ClearNextId();

static int next_player_id;

//OTC Constructor, sets up inventory
Player(std::string);


//Getters for owned Nodes and Edgess (returns a vector of pointers to them)

std::vector<Node*> GetOwnedNodes(GameBoard*);
std::vector<Edge*> GetOwnedEdges(GameBoard*);



void AddResourceCard(int,Resource);


//Take Building count piece when building it 
void TakeSettlementPiece();
void TakeCityPiece();
void TakeRoadPiece();

//Give back when upgrading to city
void GiveBackSettlementPiece();

//Take Resources for building
void TakeBuildingResources(std::map<Resource,int>);

bool CanAfford(std::map<Resource,int>);

//for std::map
bool operator<(const Player&);

};