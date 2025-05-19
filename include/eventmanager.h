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
    Zero,WelcomeScreen,PromptPlayerCount,PromptPlayerNames,GameBoardGen,Temp
};

class EventManager
{
private:

    GameState CurrentState;
    sf::Text* firsttext;
    sf::Font font;
    
    bool advance_perm = false;
    std::string inputbuffer;

    std::vector<sf::CircleShape> TileImages;
    std::vector<sf::RectangleShape> EdgeImages;
    std::vector<sf::CircleShape> NodeImages;
    //...
    

    std::vector<Player*> vec_players;
    int player_count;
    int max_turncount;
    GameBoard* GB = nullptr;
    const std::map<Resource,int> bonus_res;
    void GiveBonusResToPlayer(Player*);

public:

    //OTC Constructor
    EventManager();
    EventManager(GameBoard*,int = 2,int = 10);

    void AdvanceCurrentState();


    void Draw(sf::RenderWindow&);

    void HandleEvent(const sf::Event&);
    
    void PromptPlayerCount();

    bool InitPlayer();
    Player* SimGame();

    char What() const; 

    int Where(char);


    void FirstTurn(Player*);

    //Itt a switch case helyet ez igy nez ki OOP modon szerintem:
    //bool CheckAllCriteria(Settlement, int);
    //bool CheckAllCriteria(City,int);
    //bool CheckAllCriteria(Road,int);

    Settlement pass_Setl();
    City pass_City();
    Road pass_Road();

    void Phase_Distribute();
    void Phase_Trade();
    void Phase_Build(Player*);

    int PromptWhere() const;
    char PromptWhat() const;


    void InitGameBoard();

    


    std::map<Resource,int> GetBuildingCost(Building::BuildingTypes);

    const std::vector<GameBoard::CritFunction>& GetCritFunctionVec(Building::BuildingTypes) const;

    GameBoard::BuildFunction GetBuildFunction(Coordinate,Player*,Building::BuildingTypes);

    bool CallAllCritFunc(const std::vector<GameBoard::CritFunction>&,Coordinate,Player*,Building::BuildingTypes) const;


};

