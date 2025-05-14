#include "player.h"
int Player::next_player_id = 0;

Player::Player(std::string in_name) : player_id(next_player_id++), player_name(in_name)
{
    //init inventory

    //init building pieces
    inventory.settlements_available = SETTLEMENT_PIECE_COUNT;
    inventory.cities_available = CITY_PIECE_COUNT;
    inventory.roads_available = ROAD_PIECE_COUNT;
    
    //init resource cards
    for(int i = 0;i<RESOURCE_COUNT;i++)
    {
        inventory.resource_cards.insert(std::make_pair(Resource((ResourceTypes)i),0));
        
        //separate into 3 lines if doesnt work
        //Resource R((ResourceTypes)i);
        //std::pair<Resource,int> temp_pair = std::make_pair(R,0);
        //inventory.resource_cards.insert(temp_pair);
    }
}

void Player::ClearNextId()
{
    next_player_id = 0;
}


//Returns a vector of the owned nodes
std::vector<Node*> Player::GetOwnedNodes(GameBoard* in_pGB)
{
    std::vector<Node*> ret_vec;
    //maybe excessive
    ret_vec.reserve(TILE_COUNT*SHAPE_NODE_COUNT);
    for(auto iter : in_pGB->Get_nodemap())
    {
        if(iter.second->GetNodeOwner() == this)
        {
            ret_vec.push_back(iter.second);
        }
    }
    return ret_vec;
}

//Returns a vector of the owned edges
std::vector<Edge*> Player::GetOwnedEdges(GameBoard* in_pGB)
{
    std::vector<Edge*> ret_vec;
    //maybe excessive
    ret_vec.reserve(TILE_COUNT*SHAPE_NODE_COUNT);
    for(auto iter : in_pGB->Get_edgemap())
    {
        if(iter.second->GetEdgeOwner() == this)
        {
            ret_vec.push_back(iter.second);
        }
    }
    return ret_vec;
}







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

bool Player::CanAfford(std::map<Resource,int> in_map)
{
    
}


