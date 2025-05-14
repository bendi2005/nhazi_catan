#include "game.h"
#include "eventmanager.h"

//for loading resources into tiles
int GameBoard::rstpindex = 0;
int GameBoard::dienumindex = 0;

Game::Game()
{
    //First: generate gameboard
    //TODO preset beker
    GameBoard g;
    //getplayercount

    //en nem akarom elhinni hogy ez 72:
    printf("\n%d\n",Edge::next_edge_id);
    
    g.PrintHarbor();
    int pc = 2;
    //getmaxturncount
    
    int mtc = 10;
    //TODO error handling
    
    EventManager EM(&g,pc,mtc);
    // Player* Winner = EM.SimGame(); 
}