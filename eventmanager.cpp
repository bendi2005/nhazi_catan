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
            
            Player* current_player = *iter_player;
            Phase_RollDice();
            Phase_Trade();
            Phase_Build(current_player);        

            
            
            //(*iter_player)->RollDice(GB);
            //(*iter_player)->Trade(GB);
            //(*iter_player)->Build(GB);
            //CheckWincon
            //itt kell initelni a refet   ??? ez mi 
        }
    }
    const Player* winner = vec_players[1];
    return winner;
}

//Player-independent
void EventManager::Phase_RollDice()
{
    //GB->RollDice();

}

//GameBoard independent
void EventManager::Phase_Trade()
{

}


void EventManager::Phase_Build(Player* current_player)
{
    //a where what vegere valahogyan meglesz egy node vagy egy edge
    //ha grafikus akkor kattintassal a konkret a pozbol, ha nyillal akkor id
    //ha nem grafikus akkor id
    //amig nem grafikus (lehet utana is) addig kell egy find_type_by_id.
    //debug: where az egy id a what egy Building (a whaton beluli switchcase megoldja passal)

    //TODO error handling
    
    //1. where
    int foo = PromptWhere(); //ez csak egy prompt

    //2. what
    char c = PromptWhat();
    Building::BuildingTypes type = Building::GetTypeFromChar(c);

    //3. possible
    
    //economy
    bool a = current_player->CanAfford(GetBuildingCost(type));
    
    //placement
    bool b = CallAllCritFunc(GetCritFunctionVec(type),GB->id_to_coord(foo,type),current_player,type);
    


    //4. build
    GB->(*GameBoard::BuildFunction)


}

bool EventManager::CallAllCritFunc(const std::vector<GameBoard::CritFunction>& in_func_vector,Coordinate in_coord,Player* current_player,Building::BuildingTypes type) const
{
    for(auto critfunc : in_func_vector)
    {
        if(!((GB->*critfunc)(in_coord,current_player)))
        {
            return false;
        }
    }
    return true;
}




std::map<Resource,int> EventManager::GetBuildingCost(Building::BuildingTypes btype)
{
    //itt lehet baja lesz hogy nincs default de mi tudjuk hogy ezt kezeljuk (criteria)
    switch(btype)
    {
        case Building::BuildingTypes::SETTLEMENT :
            return Settlement::GetCost();
        case Building::BuildingTypes::CITY :
            return City::GetCost();
        case Building::BuildingTypes::ROAD :
            return Road::GetCost();
    }
}
const std::vector<GameBoard::CritFunction>& EventManager::GetCritFunctionVec(Building::BuildingTypes btype) const
{
    //note: might be static but i dont think so
    switch(btype)
    {
        case Building::BuildingTypes::SETTLEMENT :
            return GB->GetSettlementCriteriaFunction();
        case Building::BuildingTypes::CITY :
            return GB->GetCityCriteriaFunction();
        case Building::BuildingTypes::ROAD :
            return GB->GetRoadCriteriaFunction();
    }

}
GameBoard::BuildFunction EventManager::GetBuildFunction(Coordinate in_coord,Player* in_player,Building::BuildingTypes btype)
{
    switch(btype)
    {
        case Building::BuildingTypes::SETTLEMENT :
            return GB->GetSettlementBuildFunction();
        case Building::BuildingTypes::CITY :
            return GB->GetUpgradeSettlementFunction();
        case Building::BuildingTypes::ROAD :
            return GB->GetRoadBuildFunction();
    }
} 

//ezen biztos lehetne kicsit pofasitani de a fejleszto akarata hianyaban
//ezen modositasok elmaradnak.
//bool EventManager::CheckAllCriteria(Settlement type,int in_id)
//{
//    
//    //affordos cuccok
//
//    
//    
//    //placementes cuccok
//
//    return;
//}
//
//bool EventManager::CheckAllCriteria(City type,int in_id)
//{
//
//}
//bool EventManager::CheckAllCriteria(Road type,int in_id)
//{
//}




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


