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



void Player::AddResourceCard(int n,Resource in_r)
{
    //debug
    printf("Added %d of %s to %s\n",n,in_r.EnumToString().c_str(),GetName().c_str());

    inventory.resource_cards.at(in_r) += n;
}

const std::string Player::GetName() const
{
    return player_name;
}


void Player::TakeSettlementPiece()
{
    inventory.settlements_available--;
}

void Player::TakeCityPiece()
{
    inventory.cities_available--;
}

void Player::TakeRoadPiece()
{
    inventory.roads_available--;
}


void Player::GiveBackSettlementPiece()
{
    inventory.settlements_available++;
}

//Decrease each resource type by the cost of it (the ones wiht 0 stay the same)
void Player::TakeBuildingResources(std::map<Resource,int> in_map)
{
    for(auto iter : in_map)
    {
        inventory.resource_cards.at(iter.first) -= iter.second;
    }
}


bool Player::CanAfford(std::map<Resource,int> in_map)
{
    for(auto kvp_res_int : in_map)
    {
        if(inventory.resource_cards.at(kvp_res_int.first) < kvp_res_int.second)
        {
            return false;
        }
    }
    return true;
}

bool Player::operator<(const Player& other)
{
    return (this->player_name < other.player_name);
}


