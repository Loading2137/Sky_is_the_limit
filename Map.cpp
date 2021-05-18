#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Map.h>
#include <Colision.h>

float grid_size=60.f;

void Level_Platforms::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(int i=0; i<Platforms.size(); i++)
    {

        target.draw(Platforms[i],states);
    }

}
void Level_Walls::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(int i=0; i<Walls.size(); i++)
    {
        target.draw(Walls[i],states);
    }
}

Level_Platforms::Level_Platforms()
{

    sf::RectangleShape Platform1 (sf::Vector2f(6*grid_size,grid_size));
    Platform1.setPosition(350.f,700.f);

    sf::RectangleShape Platform2 (sf::Vector2f(6.5*grid_size,grid_size));
    Platform2.setPosition(180.f,600.f);
    Platform2.setFillColor(sf::Color(150,150,150));

    sf::RectangleShape Platform3 (sf::Vector2f(9*grid_size,grid_size));
    Platform3.setPosition(400.f,380.f);

    sf::RectangleShape Platform4 (sf::Vector2f(15*grid_size,grid_size));
    Platform4.setPosition(900.f,200.f);

    sf::RectangleShape Platform (sf::Vector2f(900.f,grid_size));
    Platform4.setPosition(900.f,200.f);

    sf::RectangleShape Phantom (sf::Vector2f(1.f,1.f));
    Phantom.setPosition(1950.f,1200.f);


    Platforms.push_back(Platform1);
    Platforms.push_back(Platform2);
    Platforms.push_back(Platform3);
    Platforms.push_back(Platform4);
    Platforms.push_back(Phantom);



}
std::vector<sf::FloatRect> Level_Platforms::PlatformBounds()
{
    std::vector<sf::FloatRect> CakeIsALie{};
    for(auto &i : Platforms)
    {
        sf::FloatRect wallBounds = i.getGlobalBounds();
        CakeIsALie.push_back(wallBounds);


    }
    return CakeIsALie;
}

Level_Walls::Level_Walls()
{
    sf::RectangleShape Floor (sf::Vector2f(30*grid_size,grid_size));
    Floor.setPosition(60.f,1020.f);

    sf::RectangleShape Wall_left (sf::Vector2f(grid_size,18*grid_size));
    Wall_left.setPosition(0,0.f);

    sf::RectangleShape Wall_right (sf::Vector2f(grid_size,18*grid_size));
    Wall_right.setPosition(1860.f,0.f);

    sf::RectangleShape Phantom (sf::Vector2f(1.f,1.f));
    Phantom.setPosition(1950.f,1200.f);



    Walls.push_back(Floor);
    Walls.push_back(Wall_left);
    Walls.push_back(Wall_right);
    Walls.push_back(Phantom);



}

sf::FloatRect Level_Walls::RightWallBound()
{
    return Walls[2].getGlobalBounds();
}
sf::FloatRect Level_Walls::LeftWallBound()
{
    return Walls[1].getGlobalBounds();
}
sf::FloatRect Level_Walls::BottomWallBound()
{
    return Walls[0].getGlobalBounds();
}



