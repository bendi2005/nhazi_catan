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


//ezen biztos lehetne kicsit pofasitani de a fejleszto akarata hianyaban
//ezen modositasok elmaradnak.
bool EventManager::CheckAllCriteria(Settlement type,int in_id)
{
    
    //affordos cuccok

    
    
    //placementes cuccok

    return;
}

bool EventManager::CheckAllCriteria(City type,int in_id)
{

}
bool EventManager::CheckAllCriteria(Road type,int in_id)
{
}


Settlement EventManager::pass_Setl()
{
    Settlement S;
    return S;
}
City EventManager::pass_City()
{
    City C;
    return C;
}
Road EventManager::pass_Road()
{
    Road R;
    return R;
}


char EventManager::What() const
{
        printf("Specify WHAT you want to build: ");
        std::string temp;
        //TODO Error handling
        scanf("%s",temp);

        return std::tolower(temp[0]);
}

int EventManager::Where(char in_type) 
{
    printf("Specify WHERE you want to build: ");
    int pass_id;
    bool possible = false;
    scanf("%d",pass_id);
    switch(in_type)
    {
        case 's': {
            //settlement criteria
            //TODO can afford, thats in checkall
            possible = CheckAllCriteria(pass_Setl(),pass_id);
            break;
        }
        case 'c': {
            //city criteria
            //TODO can afford, thats in checkall
            possible = CheckAllCriteria(pass_City(),pass_id);
            break;  
        }
        case 'r':{
            //road criteria
            //TODO can afford, thats in checkall
            possible = CheckAllCriteria(pass_Road(),pass_id);
            break;
        }
        default:    
            printf("Error: invalid building type.\n");
            //ez csak jo
            Where(What()); 
    }
    if(possible)
    {
        return pass_id;
    } else 
    {
        //TODO error handling
        //needs some work but you get the gist
        printf("Error: can't build there mate.\nDo you want to build [E]lsewhere or another [T]ype of building or [Q]uit");
        //depending on scanf: ...
    }
    return pass_id;
}


