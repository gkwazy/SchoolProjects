#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "AAA Game", sf:: Style::Titlebar | sf::Style::Close);
    sf::Event ev;
    
    //Game loop
    while(window.isOpen()){
     //event polling
        while (window.pollEvent(ev)){
            switch (ev.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(ev.key.code == sf::Keyboard::Escape){
                        window.close();
                        break;
                    }
            }
        }
        window.clear(sf::Color::Blue);//Clear old Frame
        
        //game code. 
        
        window.display();//tell app taht window is done drawing
        
    }
    //end of application
    return 0;
}
