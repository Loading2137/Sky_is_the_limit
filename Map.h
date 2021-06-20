#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>

class Tutorial
{
    std::vector<sf::Sprite> Tutorial_Box;
    std::vector<sf::IntRect> keyAnimation;

public:
    Tutorial();
    int step(float Second, double animation_fps);
    int Current_frame=0;
    sf::IntRect getCurrentRect(int Current_frame);
};


class Map_Texture    : public sf::Drawable
{
    std::vector<sf::Sprite> Texture_Box;
    std::vector<sf::IntRect> Chest_Position;
    std::ifstream map;
    Tutorial animation;

public:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Map_Texture();
    sf::Texture Walls_Texture;
    sf::Texture Chest_Texture;
    sf::Texture Door_Texture;
    sf::Texture W_Texture;
    sf::Texture E_Texture;
    sf::Texture R_Texture;
    sf::Texture A_Texture;
    sf::Texture S_Texture;
    sf::Texture D_Texture;
    sf::Texture F_Texture;
    sf::Texture C_Texture;

    sf::Sprite Walls;
    sf::Sprite Chest;
    sf::Sprite Door;
    sf::Sprite W;
    sf::Sprite E;
    sf::Sprite R;
    sf::Sprite A;
    sf::Sprite S;
    sf::Sprite D;
    sf::Sprite F;
    sf::Sprite C;

    sf::Font font;
    sf::Text Tutorial1_1;
    sf::Text Tutorial1_2;
    sf::Text Tutorial1_3;
    sf::Text Tutorial1_4;

    sf::Texture Pop_up;
    sf::Sprite Pop_up_window;
    std::vector<bool> is_chest_open();
    void placement(sf::FloatRect Player_Bounds);
    void key_animation(float Second, float camera);
    void is_this_fresh_file(bool it_is, std::vector<bool> chest);
    void reset();
};


class Level_Platforms :public sf::Drawable
{
    sf::Texture Walls_Texture;
    std::ifstream map;

public:
    std::vector<sf::RectangleShape> Platforms;
    std::vector <sf::RectangleShape> single_platform;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Level_Platforms();
    std::vector<sf::FloatRect> PlatformBounds();
    void scale(int scale_factor);

};


class BackGround :public sf::Drawable
{
    sf::Sprite BackGround_T;
public:
    sf::Texture BackGround_Texture;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    BackGround();

};
