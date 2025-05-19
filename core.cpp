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
