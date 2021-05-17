#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Player    :public sf::Drawable
{
    std::vector<sf::RectangleShape> Player_Box;
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Player();
    void Movement(float Second);


};

