#include "../include/eventmanager.h"


//OTC Constructor
EventManager::EventManager()
{
    CurrentState = GameState::Zero;
    player_count = 0;
    if(!(font.openFromFile("Ubuntu.ttf")))
    {
        printf("\nSomething wrong with font\n");
        return;
    }

    firsttext = new sf::Text(font);
    firsttext->setString("Welcome to Catan! Press any key to continue...");
    firsttext->setCharacterSize(40);

    firsttext->setFillColor(sf::Color::White);
    firsttext->setPosition({550,400});
}

void EventManager::Draw(sf::RenderWindow& window)
{

    window.clear(sf::Color::Black);
    switch(CurrentState)
    {
        case GameState::Zero :
            window.clear(sf::Color::Blue);
            window.draw(*firsttext);
            AdvanceCurrentState();
            break;

        case GameState::WelcomeScreen :
            window.clear(sf::Color::Blue);
            
            window.draw(*firsttext);
            if(advance_perm)
            {
                    
                AdvanceCurrentState();
                advance_perm = false;
            }
            break;    
        case GameState::PromptPlayerCount :
            window.clear(sf::Color::Blue);
            window.draw(*firsttext);
            if(advance_perm)
            {   
                AdvanceCurrentState();
                advance_perm = false;
            }
            break;
        case GameState::PromptPlayerNames :
            window.clear(sf::Color::Green);
            window.draw(*firsttext);
            if(advance_perm)
            {
                AdvanceCurrentState();
                advance_perm = false;
            }
            
            
        //...


    }
}

void EventManager::AdvanceCurrentState()
{
    switch(CurrentState)
    {
        case GameState::Zero :
            CurrentState = GameState::WelcomeScreen;
            break;
        case GameState::WelcomeScreen :
            CurrentState = GameState::PromptPlayerCount;
            break;
        case GameState::PromptPlayerCount :
            CurrentState = GameState::PromptPlayerNames;
            break;
        case GameState::PromptPlayerNames :
            CurrentState = GameState::SetupPhase;
            break;
        //...




    }
}


void EventManager::HandleEvent(const sf::Event& event)
{
    switch(CurrentState)
    {
        case GameState::Zero :
            std::this_thread::sleep_for(std::chrono::milliseconds(220));
            break;
        case GameState::WelcomeScreen :
            if(const auto* keyrelased = event.getIf<sf::Event::KeyReleased>())
            {
                
                PromptPlayerCount();  
                advance_perm = true; 
            } else if(const auto* mouseclicked = event.getIf<sf::Event::MouseButtonReleased>())
            {
                
                PromptPlayerCount();
                advance_perm = true;
            }
            break;
        case GameState::PromptPlayerCount :
            if(const auto* textentered = event.getIf<sf::Event::TextEntered>())
            {
                if(textentered->unicode >= '2' && textentered->unicode <= '9')
                {
                    player_count = textentered->unicode-'0';
                    firsttext->setString("Please enter name for Player 1:");
                    advance_perm = true;
                    Player::ClearNextId();
                } else 
                {
                    firsttext->setString("Please enter a number between 2 and 9");
                }
            }
            break;
        case GameState::PromptPlayerNames :
            if(const auto* textentered = event.getIf<sf::Event::TextEntered>())
            {
                if((textentered->unicode == '\b') && (!inputbuffer.empty()) ) //backspace
                {
                    inputbuffer.pop_back();
                    firsttext->setString(inputbuffer);
                } else if((textentered->unicode == '\r') || (textentered->unicode == '\n') ) //enter
                {
                    if(InitPlayer()) //all players initialized
                    {
                        inputbuffer.clear();
                        //after this setup phase begins
                        //placeholder:
                        firsttext->setString("So far so good");
                        advance_perm = true;
                    } else
                    {
                        inputbuffer.clear();
                        firsttext->setString("Please enter name for Player " + std::to_string(Player::GetNextPlayerId()+1) + ": ");
                    }
                } else if(textentered->unicode < '128') //valid char typed
                {
                    inputbuffer += static_cast<char>(textentered->unicode);
                    firsttext->setString(inputbuffer);
                }
                
            } 
            
            break;
        case GameState::SetupPhase :
            break;

    }
    return;
}

void EventManager::PromptPlayerCount()
{
    firsttext->setString("Enter how many players: (2-9)");
}


//EventManager::EventManager(GameBoard* in_pGB,int in_pcount,int in_max_turncount) : GB(in_pGB), player_count(in_pcount), max_turncount(in_max_turncount), bonus_res{{BRICK,4},{LUMBER,4},{WOOL,2},{GRAIN,2}}
//{
//    InitPlayer(player_count);
//
//}



bool EventManager::InitPlayer()
{
    
    Player* p = new Player(inputbuffer);
    vec_players.push_back(p);    
    printf("mi a kurva anyam van: %d %d\n",p->GetPlayerId(),player_count-1);
    return (p->GetPlayerId() == player_count-1);
    
}

void EventManager::GiveBonusResToPlayer(Player* in_player)
{
    for(auto kvp_res_int : bonus_res)
    {
        in_player->AddResourceCard(kvp_res_int.second,kvp_res_int.first);
    }
}

void EventManager::FirstTurn(Player* in_player)
{
    
    //settlement
    Player* current_player = in_player;
    
    //1. What = Settlement
    
    //2. Where
    
    int foo = PromptWhere();

    //3. Possible
    //Economy possible 
    //placement
    bool possible = CallAllCritFunc(GB->GetFirstTurnSettlementCriteria(),GB->id_to_coord(foo,Building::BuildingTypes::SETTLEMENT),current_player,Building::BuildingTypes::SETTLEMENT);
    
    //4. Build
    if(possible)
    {
        (GB->*(GB->GetSettlementBuildFunction()))(GB->id_to_coord(foo, Building::BuildingTypes::SETTLEMENT), current_player,Building::BuildingTypes::SETTLEMENT);
    } else 
    {
        printf("gatya");
    }
    //roadbuild + give rs

    //1. What = Road

    //2. Where
    foo = PromptWhere();
    
    //3. Possible
    //placement
    possible = CallAllCritFunc(GB->GetRoadCriteriaFunction(),GB->id_to_coord(foo,Building::BuildingTypes::ROAD),current_player,Building::BuildingTypes::ROAD);
    
    //4. Build
    if(possible)
    {
        (GB->*(GB->GetRoadBuildFunction()))(GB->id_to_coord(foo, Building::BuildingTypes::ROAD), current_player,Building::BuildingTypes::ROAD);
    } else 
    {
        printf("gatya");
    }
}


Player* EventManager::SimGame()
{
    //First Turn 
    //note: this wont affect wincon
    for(int i = 0;i<player_count;i++)
    {
        FirstTurn(vec_players[i]);
    }

    //Second turn (reversed order)
    for(int i = player_count-1;i>=0;i--)
    {
        FirstTurn(vec_players[i]);
    }
    
    printf("Setup over\n");
    
    bool wincon = false;
    while(!wincon)
    {
        //Turns
        
        //Iter thru players
        for(auto iter_player = vec_players.begin();iter_player != vec_players.end();iter_player++)
        {
            
            
            Player* current_player = *iter_player;  
            Phase_Distribute();
            Phase_Trade();
            Phase_Build(current_player);        

            
            
            //(*iter_player)->RollDice(GB);
            //(*iter_player)->Trade(GB);
            //(*iter_player)->Build(GB);
            //CheckWincon
            //itt kell initelni a refet   ??? ez mi  ???tovabbra se tudom
        }
    }
    Player* winner = vec_players[1];
    return winner;
}

void EventManager::Phase_Distribute()
{
    
    GB->DistributeResources();
}

//GameBoard independent //TODO
void EventManager::Phase_Trade()
{
    //todo
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
    if(!a)
    {
        printf("cant afford\n");
    }
    //debug: 
    a = true;
    
    
    //placement
    bool b = CallAllCritFunc(GetCritFunctionVec(type),GB->id_to_coord(foo,type),current_player,type);
    
    
    //4. build
    if(a && b)
    {
        (GB->*(GetBuildFunction(GB->id_to_coord(foo, type), current_player, type)))(GB->id_to_coord(foo, type), current_player,type);
    
    } else 
    {
        //error
    }
    printf("first buildphase done\n");
    



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
        case Building::BuildingTypes::EMPTY :
            printf(":(");
    }
} 

char EventManager::PromptWhat() const
{
        printf("Specify WHAT you want to build: ");
        std::string temp;
        //TODO Error handling
            scanf("%s",temp.c_str());

        return std::tolower(temp[0]);
}

int EventManager::PromptWhere() const
{
    printf("Specify WHERE you want to build: ");
    int n;
    //TODO error handing
    scanf("%d",&n);
    if(n<0)
    return n;
}
