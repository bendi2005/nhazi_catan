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



public:

//debug only
EventManager();


//OTC Constructor
EventManager(GameBoard*,int = 2,int = 10);


void InitPlayers(int);
const Player* SimGame();

char What() const; 

int Where(char);




//Itt a switch case helyet ez igy nez ki OOP modon szerintem:
//bool CheckAllCriteria(Settlement, int);
//bool CheckAllCriteria(City,int);
//bool CheckAllCriteria(Road,int);

Settlement pass_Setl();
City pass_City();
Road pass_Road();

void Phase_RollDice();
void Phase_Trade();
void Phase_Build(Player*);

int PromptWhere();
char PromptWhat();


//Kerdes ez igy rendben van?


std::map<Resource,int> GetBuildingCost(Building::BuildingTypes);

const std::vector<GameBoard::CritFunction>& GetCritFunctionVec(Building::BuildingTypes) const;

bool CallAllCritFunc(Coordinate,Player*,Building::BuildingTypes) const;


};

