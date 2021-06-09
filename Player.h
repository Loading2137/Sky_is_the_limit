#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player_Animation
{
    std::vector<sf::IntRect> idleAnimation;
    std::vector<sf::IntRect> runningAnimation;
    std::vector<sf::IntRect> jumpingAnimation;


public:


    Player_Animation();
    int step(float delta, int animation_fps);
    int jump(float delta, int animation_fps);
    int Current_frame=0;
    sf::IntRect getCurrentRect(int Current_frame);

};

class Player    :public sf::Drawable
{
    std::vector<sf::RectangleShape> Player_Box;


public:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Player();
    void Movement(float Second, int window_value);
    void Movement_Again(float Second, int window_value);
    sf::Vector2f Position();
    sf::Texture Player_Texture();
    void Collisions(float Second,int window_value);
    void scale(int scale);



};

class Player_Texture    : public sf::Drawable
{
    std::vector<sf::Sprite> Texture_Box;
    Player_Animation animation;

public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    Player_Texture();
    sf::Texture Texture;
    void Movement_T(sf::Vector2f position, float Second);
    void scale(int scale);

};

class Player_Sounds     :public sf::Sound
{
    sf::SoundBuffer Buffer_jump;
    sf::SoundBuffer Buffer_run;
    sf::Sound Sound_jump;
    sf::Sound You_say_run;

public:
    Player_Sounds();

    void Sound_movement(int window_value);


};

