#pragma once
#include <string>
#include <stdio.h>

#include "settlement.h"
#include "city.h"
#include "road.h"
#include "nodes.h"
#include "edges.h"
#include "gameboard.h"

class GameBoard;
class Edge;
class Node;
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
    static int next_player_id;
    Inventory inventory;

public:

//Called for idk what
static void ClearNextId();


std::string PlayerInfoString();


//OTC Constructor, sets up inventory
Player(std::string);


//Getters for owned Nodes and Edgess (returns a vector of pointers to them)

std::vector<Node*> GetOwnedNodes(GameBoard*);
std::vector<Edge*> GetOwnedEdges(GameBoard*);

const std::string GetName() const;
const int GetPlayerId() const;
static const int GetNextPlayerId();

void AddResourceCard(int,Resource);


//Take Building count piece when building it 
void TakeSettlementPiece();
void TakeCityPiece();
void TakeRoadPiece();

Inventory GetInventory();

//Give back when upgrading to city
void GiveBackSettlementPiece();

//Take Resources for building
void TakeBuildingResources(std::map<Resource,int>);

bool CanAfford(std::map<Resource,int>);

//for std::map
bool operator<(const Player&);

};