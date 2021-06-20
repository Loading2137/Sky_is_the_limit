#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//###########################################################################################################
class Player    :public sf::Drawable
{
    std::vector<sf::RectangleShape> Player_Box;
public:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Player();
    sf::Texture Player_Texture();
    sf::FloatRect Player_bounds();
    sf::Vector2f Reaction(sf::FloatRect Platform, sf::FloatRect Player);
    sf::Vector2f getPosition(int number_of_saves, sf::Vector2f Spawn);
    sf::Vector2f Position();
    float camera_position(int window_value, float current_position);
    void Movement(float Second, int window_value, std::vector<bool> abilities);
    void Collisions(int window_value);
    void scale(int scale);
};

//###########################################################################################################
class Player_Animation :public sf::Drawable
{

    std::vector<sf::IntRect> idleAnimation;
    std::vector<sf::IntRect> runningAnimation;
    std::vector<sf::IntRect> jumpingAnimation;
    std::vector<sf::IntRect> dashAnimation;
    sf::IntRect wall_grabAnimation;


    std::vector<sf::IntRect> RAnimation;

    sf::RectangleShape dash_outline1;
    sf::RectangleShape dash_outline2;
    sf::RectangleShape dash_outline3;
    sf::RectangleShape dash_outline4;

    sf::RectangleShape dash_bar;

public:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Player_Animation();
    int step(float delta, double animation_fps);
    void dash_bar_animation(float Position, float Second);
    int Dash();
    int Current_frame=0;
    int CurrentDash_frame=0;
    sf::IntRect getCurrentRect(int Current_frame);

};

//###########################################################################################################
class Player_Texture    : public sf::Drawable
{
    std::vector<sf::Sprite> Texture_Box;
    Player_Animation animation;

public:
    sf::Texture Texture;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Player_Texture(); 
    void Movement_T(sf::Vector2f position, float Second);
    void scale(int scale);


};

//###########################################################################################################
class Player_Sounds     :public sf::Sound
{
    sf::SoundBuffer Buffer_jump;
    sf::SoundBuffer Buffer_run;
    sf::SoundBuffer Buffer_double_jump;
    sf::SoundBuffer Bruh_buffer;
    sf::SoundBuffer yamete_buffer;

    sf::Sound Bruh_sound;
    sf::Sound yamete_sound;
    sf::Sound Sound_Double_jump;
    sf::Sound Sound_jump;
    sf::Sound You_say_run;

public:
    Player_Sounds();
    void reset();
    void file_exist(std::vector<bool> chests);
    void Sound_movement(int window_value, std::vector<bool>  bruh);
    void ON_OFF_Sound();


};

//###########################################################################################################
