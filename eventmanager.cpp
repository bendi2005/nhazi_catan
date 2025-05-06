#include "eventmanager.h"

//debug only
EventManager::EventManager()
{
    printf("event default\n");
}


void EventManager::InitPlayers(int in_playercount)
{
    //for inpc
    in_playercount += 0; //nowarning
    //Player::ClearNextId();
    Player* P = new Player("Cica");
    vec_players.push_back(P);
    P = new Player("Kutya");
    vec_players.push_back(P);
    
}


//OTC Constructor
EventManager::EventManager(GameBoard* in_pGB,int in_pcount,int in_max_turncount) : GB(in_pGB), player_count(in_pcount), max_turncount(in_max_turncount)
{
    InitPlayers(player_count);
    
}


const Player* EventManager::SimGame()
{
    //First Turn 
    //note: this wont affect wincon
    for(int i = 0;i<player_count;i++)
    {
        vec_players[i]->FirstTurnSet(GB);
        vec_players[i]->FirstTurnRoad(GB);
    }
    for(int i = player_count;i>0;i--)
    {
        vec_players[i]->FirstTurnSet(GB);
        vec_players[i]->FirstTurnRoad(GB);
    }
    
    bool wincon = false;
    while(!wincon)
    {
        //Turns
        
        //Iter thru players
        for(auto iter_player = vec_players.begin();iter_player != vec_players.end();iter_player++)
        {
            
            //Ennek van egy sokkal egyszerubb megoldasa nem kell a switch case
             
            ////Iter thru actions
            //for(int i = 0;i<ACTION_COUNT;i++)
            //{
            //    //switch case enumokkal    
            //}

            (*iter_player)->RollDice(GB);
            (*iter_player)->Trade(GB);
            (*iter_player)->Build(GB);
            //CheckWincon
            //itt kell initelni a refet
        }
    }
    const Player* winner = vec_players[1];
    return winner;
}