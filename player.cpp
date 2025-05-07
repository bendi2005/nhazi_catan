#include "player.h"
int Player::next_player_id = 0;

Player::Player(std::string in_name) : player_id(next_player_id++), player_name(in_name)
{
    //init inventory
    
    inventory.settlements_available = SETTLEMENT_PIECE_COUNT;
    inventory.cities_available = CITY_PIECE_COUNT;
    inventory.roads_available = ROAD_PIECE_COUNT;
    for(int i = 0;i<RESOURCE_COUNT;i++)
    {
        inventory.resource_cards.insert(std::make_pair(Resource((ResourceTypes)i),0));
        
        //separate into 3 lines if doesnt work
        //Resource R((ResourceTypes)i);
        //std::pair<Resource,int> temp_pair = std::make_pair(R,0);
        //inventory.resource_cards.insert(temp_pair);
    }
}

//void Player::ClearNextId()
//{
//    next_id = 1;
//}

void Player::FirstTurnSet(GameBoard* in_pGB)
{
    printf("\nfirst set\n");

    //Choose what=Set

    //Choose where
    
    
    //Check if available

    
    //Buildit


}

void Player::FirstTurnRoad(GameBoard* in_pGB)
{
    printf("\nFirst road\n");
}

void Player::RollDice(GameBoard* in_pGB)
{
    printf("\n\nroll");
}

void Player::Trade(GameBoard* in_pGB)
{
    printf("\nTrade\n");
}

void Player::Build(GameBoard* in_pGB)
{
    printf("\nbuild\n");
}

bool Player::operator<(const Player& other)
{
    return (this->player_name < other.player_name);
}