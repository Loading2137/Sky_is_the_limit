#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Map.h>

int main()
{

    int screen_height = 1080;
    int screen_width = 1920;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Sky Is The Limit");
    sf::Clock deltaClock;

    Player p1;
    Level_Platforms p2;
    Level_Walls p3;

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time Delta = deltaClock.restart();
        float Second = Delta.asSeconds();


        p1.Movement(Second);


        window.clear(sf::Color::Black);
        window.draw(p1);
        window.draw(p2);
        window.draw(p3);
        //player.drawTo(window);

        window.display();
    }
    return 0;
}
