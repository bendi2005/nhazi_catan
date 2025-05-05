#include "game.h"
#include <string>
class Player
{
private:
    static int next_id;
    int id;
    std::string player_name;

public:


//OTC Constructor
Player(std::string);


//Actions
void FirstTurn();

void RollDice();
//aki eros itt meghivja a gameboard distribut fuggvenyet

void Trade();
//na ezen majd gondolkozunk meg

void Build();
//jo itt is majd lesz valami
};