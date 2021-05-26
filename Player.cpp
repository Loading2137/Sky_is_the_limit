#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Map.h>
#include <Colision.h>

Level_Platforms p1;
Level_Walls p2;
Player_Animation p3;
std::vector<sf::FloatRect>PlatformBounds = p1.PlatformBounds();
sf::FloatRect BottomWall = p2.BottomWallBound();
sf::FloatRect LeftWall = p2.LeftWallBound();
sf::FloatRect RightWall = p2.RightWallBound();

//Gravity
float jump_speed = -1200.f;
const float gravity_const = 60.f;

bool isJumping =0;
bool onFloor =0;
float Time = 0;
float gravity = gravity_const;

void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(Player_Box[0], states);
}
void Player_Texture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(Texture_Box[0], states);
}
Player::Player()
{
    sf::RectangleShape Player(sf::Vector2f(32.f,64.f));
    Player.setPosition(sf::Vector2f(1200.f,900.f));
    Player_Box.push_back(Player);
}
Player_Texture::Player_Texture()
{
    sf::Sprite Player;
    Texture.loadFromFile("Player-Sheet.png");
    Player.setTexture(Texture);
    Player.setScale(4,4);
    Player.setPosition(sf::Vector2f(1200.f,900.f));
    Texture_Box.push_back(Player);
}
Player_Animation::Player_Animation()
{
   idleAnimation.push_back(sf::IntRect(28, 0, 8, 16));
   idleAnimation.push_back(sf::IntRect(92, 0, 8, 16));
   idleAnimation.push_back(sf::IntRect(156, 0, 8, 16));
   idleAnimation.push_back(sf::IntRect(220, 0, 8, 16));

   runningAnimation.push_back(sf::IntRect(280, 0, 12, 16));
   runningAnimation.push_back(sf::IntRect(345, 0, 10, 16));
   runningAnimation.push_back(sf::IntRect(411, 0, 8, 16));
   runningAnimation.push_back(sf::IntRect(474, 0, 10, 16));

   jumpingAnimation.push_back(sf::IntRect(541, 0, 6, 16));
   jumpingAnimation.push_back(sf::IntRect(603, 0, 10, 16));
   jumpingAnimation.push_back(sf::IntRect(667, 0, 10, 16));


   Falling_frame.push_back(sf::IntRect(667, 0, 10, 16));
}


sf::IntRect Player_Animation::getCurrentRect()
{
    return runningAnimation[3];
}

void Player_Animation ::step(float Second, int animation_fps)//, std::vector<sf::IntRect> frames)
{
        float time_between_frames=1.f/animation_fps;

        Time = Time + Second;


        if(Time>time_between_frames)
        {
            Current_frame++;
            Time= Time- time_between_frames;
            if(Current_frame ==4)//frames.size())
            {
                Current_frame=0;
            }
        }
}

void Player_Texture::Movement_T(sf::Vector2f position, float Second)
{
        animation.step(Second, 7);
        Player_Texture();
        Texture_Box[0].setTextureRect(animation.getCurrentRect());
        Texture_Box[0].setPosition(position);

}

void Player::Movement(float Second, int window_value)
{
    if(window_value==6)
    {
        sf::Vector2f velocity;
        velocity.x=0.f;
        velocity.y=0.f;
        sf::FloatRect PlayerBounds = Player_Box[0].getGlobalBounds();

        float movement_speed = 400.f;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x += -movement_speed*Second;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x += movement_speed*Second;
        }

        if((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) ){
            isJumping=1;
            onFloor=0;



        }

        if(isJumping)       // when jumping
        {

            Time +=Second;
            velocity.y=-1200.f*Second;
            std::cout<<Time<<std::endl;
            if(Time>1.f)
            {
                isJumping=0;
                velocity.y=1200.f*Second;
                Time=0;
            }


            //            gravity +=(gravity_const *Time*Time)/2.f;
            //            velocity.y +=(jump_speed+ gravity_const)*Second;


            for(auto &i : PlatformBounds)
            {
                sf::FloatRect wallBounds = i;

                if(wallBounds.intersects(PlayerBounds))
                {

                    if(PlayerBounds.top < wallBounds.top
                            &&  PlayerBounds.top+PlayerBounds.height< wallBounds.top+wallBounds.height
                            &&  PlayerBounds.left< wallBounds.left+wallBounds.width
                            &&  PlayerBounds.left+ PlayerBounds.width> wallBounds.left)

                    {
                        Player_Box[0].setPosition(PlayerBounds.left, wallBounds.top- PlayerBounds.height);
                        velocity.y=0.f;
                        onFloor=1;
                        isJumping=0;
                        Time = 0;
                        gravity =0;
                    }

                    else if(PlayerBounds.top > wallBounds.top
                            &&  PlayerBounds.top+PlayerBounds.height> wallBounds.top+wallBounds.height
                            &&  PlayerBounds.left< wallBounds.left+wallBounds.width
                            &&  PlayerBounds.left+ PlayerBounds.width> wallBounds.left)

                    {
                        Player_Box[0].setPosition(PlayerBounds.left, wallBounds.top+ wallBounds.height);
                        velocity.y=0.f;
                    }

                    else if(PlayerBounds.left < wallBounds.left
                            &&  PlayerBounds.left+PlayerBounds.width< wallBounds.left+wallBounds.width
                            &&  PlayerBounds.top< wallBounds.top+wallBounds.height
                            &&  PlayerBounds.top+ PlayerBounds.height> wallBounds.top)

                    {
                        velocity.x=0.f;
                    }

                    else if(PlayerBounds.left > wallBounds.left
                            &&  PlayerBounds.left+PlayerBounds.width> wallBounds.left+wallBounds.width
                            &&  PlayerBounds.top< wallBounds.top+wallBounds.height
                            &&  PlayerBounds.top+ PlayerBounds.height> wallBounds.top)

                    {
                        velocity.x=0.f;
                    }
                    else onFloor =0;
                }
            }

            //Wall colision

            //Bottom collisions
            if(PlayerBounds.top+PlayerBounds.height> BottomWall.top)
            {
                Player_Box[0].setPosition(PlayerBounds.left,BottomWall.top-PlayerBounds.height);
                onFloor=1;
                isJumping=0;
                gravity =0;
                Time = 0;

                velocity.y=0.f;
            }
            //Left collision
            else if(PlayerBounds.left< LeftWall.left+LeftWall.width && PlayerBounds.left<960.f)
            {
                Player_Box[0].setPosition(LeftWall.left+LeftWall.width, PlayerBounds.top);
                velocity.x=0.f;
            }
            //Right collision
            else if(PlayerBounds.left+PlayerBounds.width> RightWall.left && PlayerBounds.left>960.f)
            {
                Player_Box[0].setPosition(RightWall.left-PlayerBounds.width, PlayerBounds.top);
                velocity.x=0.f;
            }
            else onFloor =0;
        }

        if(!onFloor)    //collisions when in air/not on floor
        {
            Time +=Second;
            gravity +=(gravity_const *Time*Time)/2.f;
            velocity.y += gravity*Second;
            //velocity.y=1200.f*Second;

            for(auto &i : PlatformBounds)       //collions with platforms
            {
                sf::FloatRect wallBounds = i;

                if(wallBounds.intersects(PlayerBounds))
                {

                    if(PlayerBounds.top < wallBounds.top
                            &&  PlayerBounds.top+PlayerBounds.height< wallBounds.top+wallBounds.height
                            &&  PlayerBounds.left< wallBounds.left+wallBounds.width
                            &&  PlayerBounds.left+ PlayerBounds.width> wallBounds.left)

                    {
                        Player_Box[0].setPosition(PlayerBounds.left, wallBounds.top- PlayerBounds.height);
                        velocity.y=0.f;
                        onFloor=1;
                        isJumping=0;
                        gravity =0;
                        Time = 0;

                    }

                    else if(PlayerBounds.top > wallBounds.top
                            &&  PlayerBounds.top+PlayerBounds.height> wallBounds.top+wallBounds.height
                            &&  PlayerBounds.left< wallBounds.left+wallBounds.width
                            &&  PlayerBounds.left+ PlayerBounds.width> wallBounds.left)

                    {
                        Player_Box[0].setPosition(PlayerBounds.left, wallBounds.top+ wallBounds.height);
                        velocity.y=0.f;
                    }

                    else if(PlayerBounds.left < wallBounds.left
                            &&  PlayerBounds.left+PlayerBounds.width< wallBounds.left+wallBounds.width
                            &&  PlayerBounds.top< wallBounds.top+wallBounds.height
                            &&  PlayerBounds.top+ PlayerBounds.height> wallBounds.top)

                    {
                        velocity.x=0.f;
                    }

                    else if(PlayerBounds.left > wallBounds.left
                            &&  PlayerBounds.left+PlayerBounds.width> wallBounds.left+wallBounds.width
                            &&  PlayerBounds.top< wallBounds.top+wallBounds.height
                            &&  PlayerBounds.top+ PlayerBounds.height> wallBounds.top)

                    {
                        velocity.x=0.f;
                    }
                    else onFloor =0;
                }
            }

            //Wall colisions

            //Bottom collisions
            if(PlayerBounds.top+PlayerBounds.height> BottomWall.top)
            {
                Player_Box[0].setPosition(PlayerBounds.left,BottomWall.top-PlayerBounds.height);
                onFloor=1;
                isJumping=0;
                gravity =0;
                Time = 0;
                velocity.y=0.f;
            }
            //Left collision
            else if(PlayerBounds.left< LeftWall.left+LeftWall.width && PlayerBounds.left<960.f)
            {
                Player_Box[0].setPosition(LeftWall.left+LeftWall.width, PlayerBounds.top);
                velocity.x=0.f;
            }
            //Right collision
            else if(PlayerBounds.left+PlayerBounds.width> RightWall.left && PlayerBounds.left>960.f)
            {
                Player_Box[0].setPosition(RightWall.left-PlayerBounds.width, PlayerBounds.top);
                velocity.x=0.f;
            }
            else onFloor =0;
        }

        if(onFloor)     //collisions with walls when on floor
        {

            //Left collision
            if(PlayerBounds.left< LeftWall.left+LeftWall.width && PlayerBounds.left<960.f)
            {
                Player_Box[0].setPosition(LeftWall.left+LeftWall.width, PlayerBounds.top);
                velocity.x=0.f;
            }
            //Right collision
            else if(PlayerBounds.left+PlayerBounds.width> RightWall.left && PlayerBounds.left>960.f)
            {
                Player_Box[0].setPosition(RightWall.left-PlayerBounds.width, PlayerBounds.top);
                velocity.x=0.f;
            }
            else onFloor =0;
        }

        Player_Box[0].move(velocity);
    }
}
sf::Vector2f Player::Position()
{
    return Player_Box[0].getPosition();
}




