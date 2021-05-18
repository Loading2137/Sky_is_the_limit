#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>


class Level_Platforms :public sf::Drawable
{
public:
    std::vector<sf::RectangleShape> Platforms;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Level_Platforms();
    std::vector<sf::FloatRect> PlatformBounds();

};

class Level_Walls :public sf::Drawable
{
public:
    std::vector<sf::RectangleShape> Walls;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Level_Walls();
    sf::FloatRect LeftWallBound();
    sf::FloatRect RightWallBound();
    sf::FloatRect BottomWallBound();

};
