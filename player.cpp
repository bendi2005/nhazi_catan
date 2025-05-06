#include "player.h"
int Player::next_id = 1;

Player::Player(std::string in_name) : id(next_id++), player_name(in_name)
{}

//void Player::ClearNextId()
//{
//    next_id = 1;
//}

void Player::FirstTurnSet(GameBoard* in_pGB)
{
    printf("\nfirst set\n");
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