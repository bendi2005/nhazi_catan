#include "../include/eventmanager.h"


//OTC Constructor
EventManager::EventManager() : bonus_res{{ResourceTypes::BRICK,4},{ResourceTypes::LUMBER,4},{ResourceTypes::WOOL,2},{ResourceTypes::GRAIN,2}}
{
    TileImages.reserve(TILE_COUNT);
    //...

    //ezt meg lehetne csinalni remember
    CurrentState = GameState::Zero;
    player_count = 0;
    if(!(font.openFromFile("Ubuntu.ttf")))
    {
        printf("\nSomething wrong with font\n");
        return;
    }

    firsttext = new sf::Text(font);
    firsttext->setString("Welcome to Catan! Press any key to continue...");
    firsttext->setCharacterSize(TEXTSIZE);

    firsttext->setFillColor(sf::Color::White);
    firsttext->setPosition({550,400});

    playername = new sf::Text(font);
    playername->setCharacterSize(TEXTSIZE);
    playername->setFillColor(sf::Color::White);
    playername->setPosition(NAME_CUR_PLAYER_POS);

    cur_player = 0;
    once = false;
    is_setup = true;
}
void EventManager::IncrementCurPlayer()
{
    if(is_setup) //setup phase?
    { 
        if(once)  //iterated through once
        {
            if(cur_player == 0) //are we back at the beginning
            {
                is_setup = false;
                return;
            } else 
            {
                cur_player--;   
                return;
            }
        } else  //havent iterated through once
        {
            if(cur_player == player_count-1) //are we at the end
            {
                once = true;
                return;
            } else 
            {
                cur_player++;
                return;
            }
        }
    } else  //not setup phase
    {
        cur_player = (cur_player + 1) % player_count;
        
        return;
    }
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
            CheckAndAdvance();
            break;    
        case GameState::PromptPlayerCount :
            window.clear(sf::Color::Blue);
            window.draw(*firsttext);
            CheckAndAdvance();
            break;
        case GameState::PromptPlayerNames :
            window.clear(sf::Color::Green);
            window.draw(*firsttext);
            CheckAndAdvance();
            break;
        case GameState::GameBoardGen :
            RegularTurnDraw(window);
            return;
        case GameState::FirstTurnSettlement :
            RegularTurnDraw(window); 
            return;
        case GameState::FirstTurnRoad :
            RegularTurnDraw(window);
            return;
        case GameState::RollDicePrompt :
            RegularTurnDraw(window);
            //CheckAndAdvance();
            return;
        case GameState::RollDice :
            RegularTurnDraw(window);
            //CheckAndAdvance();
            return;
        case GameState::AfterDiceRoll :
            RegularTurnDraw(window);
           // CheckAndAdvance();
            
        case GameState::RegularTurnBuild :
            RegularTurnDraw(window);
        case GameState::GameWon :
            RegularTurnDraw(window);
            return;
        //...

    }
    return;
}

void EventManager::CheckAndAdvance()
{
    if(advance_perm)
    {
        advance_perm = false;
        AdvanceCurrentState();
    }
}

void EventManager::RegularTurnDraw(sf::RenderWindow& window)
{
    window.clear(BACKGROUND_COLOR);
    window.draw(*firsttext);
    playername->setString("Turn of: " + vec_players[cur_player]->GetName());
    window.draw(*playername);
    DrawGB(window);
    DrawPlayerInfo(window);
    if(advance_perm)
    {
        advance_perm = false;
        AdvanceCurrentState();
    }
    return;
}

void EventManager::DrawGB(sf::RenderWindow& window)
{
    TileImages.clear();
    EdgeImages.clear();
    NodeImages.clear();
    GB->DrawTiles(&TileImages);
    GB->DrawEdges(&EdgeImages);
    GB->DrawNodes(&NodeImages);
    for(auto tile_image : TileImages)
    {
        window.draw(tile_image.first);
        tile_image.second.setFont(font);
        window.draw(tile_image.second);
    }
    for(auto edge_image : EdgeImages)
    {
        window.draw(edge_image);
    }
    for(auto node_image : NodeImages)
    {
        window.draw(node_image);
    }
}

void EventManager::DrawPlayerInfo(sf::RenderWindow& window)
{

    for(int i = 0;i<player_count;i++)
    {
        sf::Text* temp = new sf::Text(font);
        temp->setPosition({BASE_PLAYER_INFO_WIDTH,BASE_PLAYER_INFO_HEIGHT+i*PLAYER_INFO_HEIGHT_SCALE});
        temp->setFillColor(sf::Color::Red);
        temp->setCharacterSize(20);
        temp->setString(vec_players[i]->PlayerInfoString());
        window.draw(*temp);
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
            CurrentState = GameState::GameBoardGen;
            break;
        case GameState::GameBoardGen :
            CurrentState = GameState::FirstTurnSettlement;
            return;
        case GameState::FirstTurnSettlement :
            CurrentState = GameState::FirstTurnRoad;
            return;
        case GameState::FirstTurnRoad :
            IncrementCurPlayer();
            if(is_setup)
            {
                CurrentState = GameState::FirstTurnSettlement;
            } else 
            {
                CurrentState = GameState::RollDicePrompt;
                IncrementCurPlayer();
            }
            return;
        case GameState::RollDicePrompt :
            CurrentState = GameState::RollDice;
            return;
        case GameState::RollDice :
            CurrentState = GameState::AfterDiceRoll;
        case GameState::AfterDiceRoll :
            CurrentState = GameState::RegularTurnBuild;
        case GameState::RegularTurnBuild :
            if(auto* winner = IsWinner())
            {
                p_winner = winner;
                CurrentState = GameState::GameWon;
                return;
            } else if(cur_player == player_count)
            {
                IncrementCurPlayer();
                CurrentState = GameState::RollDicePrompt;
                return;
            } else 
            {
                IncrementCurPlayer();
                return;
            }
            return;
        case GameState::GameWon :
            
            return;
        //...




    }
}

std::string EventManager::WinnerText(Player* in_player)
{
    return in_player->GetName() + " has won!";
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
        case GameState::GameBoardGen :
        {    InitGameBoard();
            firsttext->setString("GameBoard rendered: do anything to continue");
            firsttext->setPosition(TEXTBOX_POS);
            return;
        }
        case GameState::FirstTurnSettlement :
        
            firsttext->setString("Click on the Node you want to build into a settlement:");
            firsttext->setPosition(TEXTBOX_POS);
            if(const auto* clicked = event.getIf<sf::Event::MouseButtonPressed>())
            {
                int try_id = GB->SettlementInRadius(clicked->position);
                if(try_id != -1)
                {
                    if(FirstTurnSettlement(vec_players[cur_player],try_id))
                    {
                        advance_perm = true;        
                    }
                }
            }
            return;
        
        case GameState::FirstTurnRoad :
            firsttext->setString("Click on the middle of the Edge you want to build into a road:");
            firsttext->setPosition(TEXTBOX_POS);
            if(const auto* clicked = event.getIf<sf::Event::MouseButtonPressed>())
            {
                int try_id = GB->RoadInRadius(clicked->position);
                if(try_id != -1)
                {
                    if(FirstTurnRoad(vec_players[cur_player],try_id))
                    {
                        advance_perm = true;
                    }
                }
            }
            return;
        case GameState::RollDicePrompt :
            firsttext->setString("Press R to roll dice");
            firsttext->setPosition(TEXTBOX_POS);
            if(const auto* pressed = event.getIf<sf::Event::KeyPressed>())
            {
                if(pressed->code == sf::Keyboard::Key::R)
                {
                    turn_roll = GB->DistributeResources();
                    advance_perm = true;
                }
            }
            return;
        case GameState::RollDice :
            
            std::this_thread::sleep_for(std::chrono::milliseconds(220));
            firsttext->setString("Rolled: " + std::to_string(turn_roll) + " press any to continue");
            firsttext->setPosition(TEXTBOX_POS);
            if(const auto* keypressed = event.getIf<sf::Event::KeyPressed>())
            advance_perm = true;
            return;
        case GameState::AfterDiceRoll :
            firsttext->setString("Rolled: " + std::to_string(turn_roll) + " press any to continue");
            firsttext->setPosition(TEXTBOX_POS);
            std::this_thread::sleep_for(std::chrono::milliseconds(220));
            if(const auto* keypressed = event.getIf<sf::Event::KeyPressed>())
            {
                advance_perm = true;
            }
	case GameState::RegularTurnBuild :

			firsttext->setString("Click on an empty Node to Build on it\nCLick on an empty Edge to build a road on it\nClick on a Settlement to upgrade it ot a City\nOr go to the [N]ext player");
			firsttext->setPosition(TEXTBOX_POS);
			if(const auto* mouseclicked = event.getIf<sf::Event::MouseButtonPressed>())
			{
                    //Settlement
                    int try_id = GB->SettlementInRadius(mouseclicked->position);
                    if(try_id != -1)
                    {
                        RegularTurnCity(vec_players[cur_player],try_id);
                        RegularTurnSettlement(vec_players[cur_player],try_id);
                    }
                    try_id = GB->RoadInRadius(mouseclicked->position);
                    if(try_id != -1)
                    {
                        RegularTurnRoad(vec_players[cur_player],try_id);
                    }
			}
            if(const auto* buttonpressed = event.getIf<sf::Event::KeyPressed>())	
			{
					if(buttonpressed->code == sf::Keyboard::Key::N)
					{
							advance_perm = true;
					}
			}
			return;
        case GameState::GameWon : 
            firsttext->setString(WinnerText(p_winner));
            return;
    }
    return;
}

Player* EventManager::IsWinner()
{
    for(auto* p : vec_players)
    {
        int svp = 0;
        for(auto* on : p->GetOwnedNodes(GB))
        {
            if(on->GetNodePointerBuilding())
            {
                svp += on->GetNodePointerBuilding()->GetVictoryPoints();
            }
        } 
        if(svp >= VICTORY_POINT_NEEDED_FOR_WIN)
        {
            return p;
        }      
    }
    return nullptr;
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
    GiveBonusResToPlayer(p);
    vec_players.push_back(p);    
    return (p->GetPlayerId() == player_count-1);
    
}

void EventManager::InitGameBoard()
{
    GB = new GameBoard;
    advance_perm = true;
}

void EventManager::GiveBonusResToPlayer(Player* in_player)
{
    for(auto kvp_res_int : bonus_res)
    {
        in_player->AddResourceCard(kvp_res_int.second,kvp_res_int.first);
    }
}

bool EventManager::FirstTurnSettlement(Player* in_player,int in_id)
{
    if(CallAllCritFunc(GB->GetFirstTurnSettlementCriteria(),GB->id_to_coord(in_id,Building::BuildingTypes::SETTLEMENT),in_player,Building::BuildingTypes::SETTLEMENT))
    {
        (GB->*(GB->GetSettlementBuildFunction()))(GB->id_to_coord(in_id, Building::BuildingTypes::SETTLEMENT), in_player,Building::BuildingTypes::SETTLEMENT);
        return true;
    } else 
    {
        firsttext->setString("Please enter a valid Node option");
        return false;
    }
}

void EventManager::RegularTurnSettlement(Player* in_player,int in_id)
{
    if((CallAllCritFunc(GB->GetSettlementCriteriaFunction(),GB->id_to_coord(in_id,Building::BuildingTypes::SETTLEMENT),in_player,Building::BuildingTypes::SETTLEMENT)) && CanAfford(in_player,Building::BuildingTypes::SETTLEMENT))
    {
        (GB->*(GB->GetSettlementBuildFunction()))(GB->id_to_coord(in_id, Building::BuildingTypes::SETTLEMENT), in_player,Building::BuildingTypes::SETTLEMENT);
        return;
    } else 
    {
        firsttext->setString("Please enter a valid Node option");
        return;
    }
}

void EventManager::RegularTurnRoad(Player* in_player,int in_id)
{
    if((CallAllCritFunc(GB->GetRoadCriteriaFunction(),GB->id_to_coord(in_id,Building::BuildingTypes::ROAD),in_player,Building::BuildingTypes::ROAD)) && CanAfford(in_player,Building::BuildingTypes::ROAD))
    {
        (GB->*(GB->GetRoadBuildFunction()))(GB->id_to_coord(in_id,Building::BuildingTypes::ROAD),in_player,Building::BuildingTypes::ROAD);
        return;
    } else 
    {
        firsttext->setString("Cant build Road");
        return;
    }
}

void EventManager::RegularTurnCity(Player* in_player,int in_id)
{
    if((CallAllCritFunc(GB->GetCityCriteriaFunction(),GB->id_to_coord(in_id,Building::BuildingTypes::CITY),in_player,Building::BuildingTypes::CITY)) && CanAfford(in_player,Building::BuildingTypes::CITY))
    {
        (GB->*(GB->GetUpgradeSettlementFunction()))(GB->id_to_coord(in_id,Building::BuildingTypes::CITY),in_player,Building::BuildingTypes::CITY);
        return;
    }
    {
        firsttext->setString("Cant build City");
        return;
    }
}



bool EventManager::FirstTurnRoad(Player* in_player,int in_id)
{
    if(CallAllCritFunc(GB->GetRoadCriteriaFunction(),GB->id_to_coord(in_id,Building::BuildingTypes::ROAD),in_player,Building::BuildingTypes::ROAD))
    {
        (GB->*(GB->GetRoadBuildFunction()))(GB->id_to_coord(in_id, Building::BuildingTypes::ROAD), in_player,Building::BuildingTypes::ROAD);
        return true;
    } else 
    {   
        firsttext->setString("Please enter a valid Edge option:");
        return false;
    }
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

bool EventManager::CanAfford(Player* in_player,Building::BuildingTypes btype)
{
    switch(btype)
    {
        case Building::BuildingTypes::SETTLEMENT :
            return (in_player->GetInventory().resource_cards.at(Resource(ResourceTypes::BRICK)) >= 1) && (in_player->GetInventory().resource_cards.at(Resource(ResourceTypes::LUMBER)) >= 1) && (in_player->GetInventory().resource_cards.at(Resource(ResourceTypes::WOOL)) >= 1) && (in_player->GetInventory().resource_cards.at(Resource(ResourceTypes::GRAIN)) >= 1) && in_player->GetInventory().settlements_available >= 1;
        case Building::BuildingTypes::ROAD :
            return (in_player->GetInventory().resource_cards.at(Resource(ResourceTypes::BRICK)) >= 1) && (in_player->GetInventory().resource_cards.at(Resource(ResourceTypes::LUMBER)) >= 1) && in_player->GetInventory().roads_available >= 1;
        case Building::BuildingTypes::CITY :
            return (in_player->GetInventory().resource_cards.at(Resource(ResourceTypes::ORE)) >= 3) && (in_player->GetInventory().resource_cards.at(Resource(ResourceTypes::GRAIN)) >= 2 )&& in_player->GetInventory().cities_available >= 1;
    }
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

