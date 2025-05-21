#include "./include/eventmanager.h"

int GameBoard::rstpindex = 0;
int GameBoard::dienumindex = 0;
int main()
{

    sf::RenderWindow window(sf::VideoMode({INDOW_SIZE_WIDTH,WINDOW_SIZE_HEIGHT}),"Catan");
    
    EventManager evman;
    
    while(window.isOpen())
    {
        while(std::optional event = window.pollEvent())
        {
            if(event->getIf<sf::Event::Closed>())
            {
                printf("close request");
                window.close();
            }
            evman.HandleEvent(*event);   
            evman.Draw(window);
            window.display();
        }
    }

    printf("done");
    return 0;
}
