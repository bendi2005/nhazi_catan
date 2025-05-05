#include "eventmanager.h"

//debug only
EventManager::EventManager()
{
    printf("event default\n");
}


void EventManager::InitPlayers(int in_playercount)
{
    Player P("Cica");
    vec_players.push_back(P);
    Player P("Kutya");
    vec_players.push_back(P);
    
}


//OTC Constructor
EventManager::EventManager(int in_pcount,int in_max_turncount) : player_count(in_pcount), max_turncount(in_max_turncount)
{
    InitPlayers(player_count);
    
    const Player& Winner = SimGame(max_turncount); 
}


const Player& EventManager::SimGame(int in_max_turncount)
{
    //First Turn 
    //note: this wont affect wincon
    for(int i = 0;i<player_count;i++)
    {
        vec_players[i].FirstTurn();
    }
    
    
    bool wincon = false;
    while(!wincon)
    {
        //Turns
        
        //Iter thru players
        for(auto iter_player = vec_players.begin();iter_player != vec_players.end();iter_player++)
        {
            //Iter thru actions
            for(int i = 0;i<ACTION_COUNT;i++)
            {
                iter_player->RollDice();
                iter_player->Trade();
                iter_player->Build();    
            }
            //CheckWincon
            //itt kell initelni a refet
        }
    }
    const Player& winner = vec_players[0];
    return winner;
}