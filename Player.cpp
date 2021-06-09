#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Player.h>
#include <Map.h>
#include <Colision.h>



//double scale_factor=1;


//void Player::scale(int scale)
//{
//     scale_factor=scale;
//}


Level_Platforms p1;
Level_Walls p2;
Player_Animation p3;
std::vector<sf::FloatRect>PlatformBounds = p1.PlatformBounds();

sf::FloatRect BottomWall = p2.BottomWallBound();
sf::FloatRect LeftWall = p2.LeftWallBound();
sf::FloatRect RightWall = p2.RightWallBound();

std::vector<sf::FloatRect>Collision_Box = p1.PlatformBounds();
std::vector<sf::Vector2f> penetrator_value;
std::vector<bool> penetrator_bool;

bool left=0;
bool already_playing=0;


//Gravity
const float jump_speed = -1200.f;
const float movement_speed = 400.f;
const float gravity_const = 20.f;

sf::Vector2f velocity;
int ground_level=1000;
bool why_are_you_running=0;
bool isJumping =0;
bool Falling=0;
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

Player_Sounds::Player_Sounds()
{
    Buffer_jump.loadFromFile("SFX_Jump_09.wav");
    Sound_jump.setBuffer(Buffer_jump);
    Sound_jump.setVolume(60);
    Buffer_run.loadFromFile("step_cloth1.ogg");
    You_say_run.setBuffer(Buffer_run);
    You_say_run.setVolume(60);
    You_say_run.setLoop(true);

}
void Player_Sounds::Sound_movement(int window_value)
{
    if(window_value==6)
    {
    std::cout<<why_are_you_running<<std::endl;
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& isJumping==0 && Falling==0)
     {
         Sound_jump.play();
     }
     if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) && isJumping==0 && Falling==0)||( sf::Keyboard::isKeyPressed(sf::Keyboard::D) && isJumping==0 && Falling==0) )
     {

         why_are_you_running=1;
     }
     else if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || !(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || isJumping==1  || Falling==1)
     {
         why_are_you_running=0;
     }

     if(why_are_you_running)
     {
        if(!already_playing)
        {
           You_say_run.play();
           already_playing=1;
        }

     }
     else if(!why_are_you_running)
     {
         You_say_run.pause();
         already_playing=0;
     }

    }
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
   jumpingAnimation.push_back(sf::IntRect(667, 0, 10, 16));

}

sf::IntRect Player_Animation::getCurrentRect(int Current_frame)
{
    if(isJumping && velocity.y<0)
    {
        return jumpingAnimation[0];
    }
    else if(velocity.y>20.f )
    {
        return jumpingAnimation[1];


    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)|| sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        return runningAnimation[Current_frame];
    }
    else if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || !(sf::Keyboard::isKeyPressed(sf::Keyboard::D)))
    {
        return idleAnimation[Current_frame];
    }
}

int Player_Animation ::step(float Second, int animation_fps)//, std::vector<sf::IntRect> frames)
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
        return Current_frame;
}

void Player_Texture::Movement_T(sf::Vector2f position, float Second)
{



        Player_Texture();
        Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 7)));
        Texture_Box[0].setPosition(position);

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {

            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 7)));
        }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {

            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 7)));
            left=0;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {

            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 7)));
            left=1;
        }

        if(left)
        {
            Texture_Box[0].setScale(-4,4);
            Texture_Box[0].setPosition(position.x+32.f, position.y);
        }
        if(!left)
        {
            Texture_Box[0].setScale(4,4);
            Texture_Box[0].setPosition(position.x-2.f, position.y);
        }


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


                        gravity +=(gravity_const *Time*Time)/2.f;
                        velocity.y +=(jump_speed+ gravity_const)*Second;


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

void Player::Movement_Again(float Second, int window_value)
{



    if(window_value==6)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            velocity.x = -movement_speed;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            velocity.x = movement_speed;
        }
        else
            velocity.x=0.f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& isJumping==0 && Falling==0) {
            velocity.y =jump_speed;

            isJumping=1;
        }

        if(Player_Box[0].getGlobalBounds().top+Player_Box[0].getGlobalBounds().height<ground_level||velocity.y<0)
        {
            velocity.y += gravity_const;
        }

        if (velocity.y>20.f )
        {
            Falling=1;
        }
//        else
//        {
//            Player_Box[0].setPosition(Player_Box[0].getPosition().x, ground_level-Player_Box[0].getGlobalBounds().height);
//            velocity.y=0.f;
//            isJumping=0;
//        }
        //std::cout<<velocity.y<<std::endl;
        Player_Box[0].move(velocity*Second);
    }

}

void Player::Collisions(float Second,int window_value)
{
    sf::FloatRect PlayerBounds = Player_Box[0].getGlobalBounds();
    if(window_value==6)
    {
        for(int i=0; i<Collision_Box.size(); i++)
        {
            std::vector<sf::Vector2f> Place_holder;
            if(PlayerBounds.intersects(Collision_Box[i]))
            {
                penetrator_bool.push_back(1);
            }
            else penetrator_bool.push_back(0);
            //bottom and left
            if(PlayerBounds.top+PlayerBounds.height>Collision_Box[i].top && PlayerBounds.left<Collision_Box[i].left+Collision_Box[i].width)
            {
                penetrator_value.push_back(sf::Vector2f (PlayerBounds.top+PlayerBounds.height-Collision_Box[i].top ,PlayerBounds.left-Collision_Box[i].left+Collision_Box[i].width));
            }
            //bottom and right
            if(PlayerBounds.top+PlayerBounds.height>Collision_Box[i].top && PlayerBounds.left+PlayerBounds.width>Collision_Box[i].left)
            {
                penetrator_value.push_back(sf::Vector2f (PlayerBounds.top+PlayerBounds.height-Collision_Box[i].top ,PlayerBounds.left-Collision_Box[i].left+Collision_Box[i].width));
            }

        }
        sf::Vector2f penetration (0.f, 0.f);
        for(auto &i : Collision_Box)
        {
            if(PlayerBounds.intersects(i))
            {
                //std::cout<<"Collision"<<std::endl;
                if(PlayerBounds.top+PlayerBounds.height>i.top)
                {
                    penetration.y=PlayerBounds.top+PlayerBounds.height-i.top;
                    Player_Box[0].setPosition(Player_Box[0].getPosition().x-penetration.x, Player_Box[0].getPosition().y-penetration.y);
                    velocity.y=0.f;
                    isJumping=0;
                    Falling=0;
                }
                else if(PlayerBounds.left<i.left+i.width)
                {
                    penetration.x=PlayerBounds.left+i.left+i.width;
                    Player_Box[0].setPosition(Player_Box[0].getPosition().x+penetration.x,Player_Box[0].getPosition().y+penetration.y);
                    velocity.x=0;
                }
                else if(PlayerBounds.left+PlayerBounds.width>i.left)
                {
                    penetration.x=PlayerBounds.left+PlayerBounds.width-i.left;
                    Player_Box[0].setPosition(Player_Box[0].getPosition().x-penetration.x,Player_Box[0].getPosition().y-penetration.y);
                    velocity.x=0;
                }





            }


        }


        //std::cout<<isJumping<<"     "<< Falling <<std::endl;


    }
}


