#include "./include/graphicmanager.h"
#include "./include/eventmanager.h"

int GameBoard::rstpindex = 0;
int GameBoard::dienumindex = 0;
int main()
{

    sf::RenderWindow window(sf::VideoMode({1800,1100}),"Catan");
    
    EventManager evman;
    
    while(window.isOpen())
    {
        while(std::optional event = window.pollEvent())
        {
            if(event->getIf<sf::Event::Closed>())
            {
                printf("\nBye bye");
                window.close();
            }
            evman.HandleEvent(*event);   
            evman.Draw(window);
            window.display();
            
            
            
 
            
            
            



        }
    }


    
    //GameBoard g;
    //GraphicManager GM(window);

    //while(window.isOpen())
    //{
    //    while(const std::optional event = window.pollEvent())
    //    {
    //        if(event->getIf<sf::Event::Closed>())
    //        {
    //            window.close();
    //        }
    //        int pc = 2;
    //        //getmaxturncount
//
    //        int mtc = 10;
    //        //TODO error handling
    //
    //        EventManager EM(&g,pc,mtc);
    //        Player* Winner = EM.SimGame(); 
//
//
//
    //    }
    //} 



    
    
    

    
    printf("done");
    return 0;
}
