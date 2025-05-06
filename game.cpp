#include "game.h"
#include "eventmanager.h"

Game::Game()
{
    //First: generate gameboard
    //TODO preset beker
    GameBoard g;
    //getplayercount
    
    g.PrintHarbor();
    int pc = 2;
    //getmaxturncount
    
    int mtc = 10;
    //TODO error handling
    
    EventManager EM(&g,pc,mtc);
    const Player* Winner = EM.SimGame(); 
}