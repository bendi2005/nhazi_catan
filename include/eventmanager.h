#pragma once
#include "player.h"
#include <SFML/Graphics.hpp> 
#include <vector>
#include <string>


#include <thread>
#include <chrono>

#include "building.h"
#include "gameboard.h"
#include "city.h"

enum class GameState
{
		Zero,
		WelcomeScreen,
		PromptPlayerCount,
		PromptPlayerNames,
		GameBoardGen,
		FirstTurnSettlement,
		FirstTurnRoad,
		RollDicePrompt,
		RollDice,
		AfterDiceRoll,
		RegularTurnBuild,
        GameWon,
};

class EventManager
{
private:

    GameState CurrentState;
    sf::Text* firsttext;
    sf::Font font;
    sf::Text* playername;

    bool advance_perm = false;
    std::string inputbuffer;

    std::vector<std::pair<sf::CircleShape,sf::Text>> TileImages;
    std::vector<sf::RectangleShape> EdgeImages;
    std::vector<sf::CircleShape> NodeImages;
    //...
    
    
    std::vector<Player*> vec_players;
    int player_count;
    int max_turncount;
    GameBoard* GB = nullptr;
    const std::map<Resource,int> bonus_res;
    void GiveBonusResToPlayer(Player*);

    int turn_roll;
    int cur_player;
    bool once;
    bool is_setup;
    Player* p_winner = nullptr;
public:



    //OTC Constructor
    EventManager();
    EventManager(GameBoard*,int = 2,int = 10);

    void AdvanceCurrentState();

    void DrawGB(sf::RenderWindow&);

    void Draw(sf::RenderWindow&);

    void HandleEvent(const sf::Event&);
    
    void PromptPlayerCount();

    bool InitPlayer();
    Player* SimGame();

    char What() const; 

    int Where(char);


    void DrawPlayerInfo(sf::RenderWindow&);
    
    
    bool FirstTurnSettlement(Player*,int);

    bool FirstTurnRoad(Player*, int);

    void RegularTurnDraw(sf::RenderWindow&);

    void RegularTurnSettlement(Player*,int);

    void RegularTurnRoad(Player*,int);

    void RegularTurnCity(Player*,int);
    
    Settlement pass_Setl();
    City pass_City();
    Road pass_Road();

    void Phase_Distribute();
    void Phase_Trade();
    void Phase_Build(Player*);

    int PromptWhere() const;
    char PromptWhat() const;


    void InitGameBoard();

    void IncrementCurPlayer();

    void CheckAndAdvance();

    bool CanAfford(Player*,Building::BuildingTypes);

    std::map<Resource,int> GetBuildingCost(Building::BuildingTypes);

    const std::vector<GameBoard::CritFunction>& GetCritFunctionVec(Building::BuildingTypes) const;

    GameBoard::BuildFunction GetBuildFunction(Coordinate,Player*,Building::BuildingTypes);

    bool CallAllCritFunc(const std::vector<GameBoard::CritFunction>&,Coordinate,Player*,Building::BuildingTypes) const;

    Player* IsWinner();

    std::string WinnerText(Player*);

};

