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

    //printf("en nem akarom elhinni hogy ez 72:\n");
    //printf("\n%d\n",Edge::next_edge_id);
    //
    //printf("node coords:\n");
    //PrintMap(g.Get_nodemap());
    //
    //printf("edge coords:\n");
    //PrintMap(g.Get_edgemap());
//
//
    //printf("tile coords:\n");
    //PrintMap(g.Get_tilemap());
    
    //for(auto temp : g.Get_edgemap())
    //{
    //    printf("id : %d ",temp.second->GetEdgeId());
    //    printf("pos x: %d pos y: %d\n",temp.second->GetPos().GetX(),temp.second->GetPos().GetY());
    //}
    //
    //printf("\n\n\n");
    //for(auto temp : g.Get_nodemap())
    //{
    //    printf("id : %d",temp.second->GetNodeId());
    //    printf("pos x: %d pos y: %d\n",temp.second->GetNodePos().GetX(),temp.second->GetNodePos().GetY());
    //
    //}
    //g.PrintHarbor();
    
    int pc = 2;
    //getmaxturncount
    
    int mtc = 10;
    //TODO error handling
    
    EventManager EM(&g,pc,mtc);

    Player* Winner = EM.SimGame(); 
}