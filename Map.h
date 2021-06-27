#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
//###########################################################################################################
class Tutorial
{
    std::vector<sf::Sprite> Tutorial_Box;
    std::vector<sf::IntRect> keyAnimation;
     std::vector<sf::IntRect> Fire_frames;

public:
    Tutorial();
    sf::IntRect step(float Second, double animation_fps, int frame_number);
    sf::IntRect step_fire(float Second, double animation_fps, int frame_number);
    int Current_frame=0;
    int Current_fire_frame=0;
    sf::IntRect getCurrentRect_key(int Current_frame);

};

//###########################################################################################################
class Map_Texture    : public sf::Drawable
{
    std::vector<sf::Sprite> Texture_Box;
    std::vector<sf::IntRect> Chest_Position;
    std::vector<sf::IntRect> Toggle_Position;

    std::ifstream map;
    Tutorial animation;
    bool Mouse_pressed=0;

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
    sf::Texture fire_texture;
    sf::Texture Toggle_Texture;

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
    sf::Sprite fireplace;
    sf::Sprite Toggle1;
    sf::Sprite Toggle2;
    sf::Sprite Toggle3;

    sf::Font font;
    sf::Text Tutorial1_1;
    sf::Text Tutorial1_2;
    sf::Text Tutorial1_3;
    sf::Text Tutorial1_4;

    sf::Texture Pop_up;
    sf::Sprite Pop_up_window;
    std::vector<bool> is_chest_open();
    int Dor(sf::FloatRect Player_Bounds);
    void Chest_state(sf::FloatRect Player_Bounds);
    void Map_animation(float Second, float camera);
    void is_this_fresh_file(bool it_is, std::vector<bool> chest);
    void reset();
    void Cheat_window(sf::Vector2f mouse_pos);
};

//###########################################################################################################
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
    std::vector<sf::RectangleShape> Last_element();

};

//###########################################################################################################
class BackGround :public sf::Drawable
{
    sf::Sprite BackGround_T;
    sf::Sprite BackGround_T2;
public:
    sf::Texture BackGround_Texture;
    sf::Texture BackGround_Texture2;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    BackGround();

};
//###########################################################################################################

class Glados :public sf::Drawable
{
    std::vector<sf::IntRect> GladosFrames;
    std::vector<sf::IntRect> idleAnimation;
    sf::Texture Glados_Texture;
    sf::Texture Cake_Texture;
    sf::Texture Player_dummy_Texture;
    sf::Texture Floor_dummy_Texture;
    sf::Texture Background_Texture;
    sf::Texture Dark_Texture;

    sf::Sprite Glados_sprite;
    sf::Sprite Cake_sprite;
    sf::RectangleShape Floor_dummy;
    sf::Sprite Player_dummy_sprite;
    sf::Sprite Background;
    sf::RectangleShape Dark;

    sf::Color Black= (sf::Color::Black);

    sf::Font font;
    sf::Text Bad_ending;


    int Current_frame=0;
    int Current_frame_p=0;

    float Phase_Time=0.f;

public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Glados();
    void Glados_animation(float Second);
    sf::IntRect step(float Second, double animation_fps, int frame_number);
    sf::IntRect step_p(float Second, double animation_fps, int frame_number);
    void Timer(float Second);
    float End();


};
