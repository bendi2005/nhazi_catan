#pragma once
#include "game.h"
#include "player.h"

//ezeket a buildingben kene?
#include "settlement.h"
#include "city.h"
#include "road.h"


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
void CheckAllCriteria(Settlement, int);
void CheckAllCriteria(City,int);
void CheckAllCriteria(Road,int);

Settlement pass_Setl();
City pass_City();
Road pass_Road();


};

