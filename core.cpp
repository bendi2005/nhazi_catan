#include "./include/eventmanager.h"

int GameBoard::rstpindex = 0;
int GameBoard::dienumindex = 0;
int main()
{

    sf::RenderWindow window(sf::VideoMode({INDOW_SIZE_WIDTH,WINDOW_SIZE_HEIGHT}),"Catan");
    try 
    {
        EventManager evman;
        while(window.isOpen())
        {   
            while(std::optional event = window.pollEvent())
            {
                if(event->getIf<sf::Event::Closed>())
                {
                    window.close();
                }
                evman.HandleEvent(*event);   
                evman.Draw(window);
                window.display();
            }
        }   
    return 0;
    }
    
    catch(sf::Exception e)  
    {
            printf("Please include Ubuntu.ttf in the directory");
            return 1;
    } 
}
