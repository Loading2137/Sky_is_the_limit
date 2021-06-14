#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Player.h>
#include <Map.h>
#include <Colision.h>


Level_Platforms p1;
Level_Walls p2;
Player_Animation p3;

sf::Vector2f Spawn_position;

sf::FloatRect BottomWall = p2.BottomWallBound();
sf::FloatRect LeftWall = p2.LeftWallBound();
sf::FloatRect RightWall = p2.RightWallBound();

std::vector<sf::FloatRect>Collision_Box = p1.PlatformBounds();
std::vector<sf::Vector2f> penetrator_value;
std::vector<bool> penetrator_bool;

bool left=0;
bool already_playing=0;
bool dash_pressed=0;
bool dash=0;
double interval=0.09539;



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
float dashTime=12;
float gravity = gravity_const;


void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(Player_Box[0], states);
}
void Player_Texture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(Texture_Box[0], states);
}


sf::Vector2f Player::getPosition(int number_of_saves, sf::Vector2f Spawn)
{
    if(number_of_saves>0)
        Player_Box[0].setPosition(Spawn);



}
Player::Player()
{
    sf::RectangleShape Player(sf::Vector2f(32.f,64.f));
    Player.setPosition(1200.f,900.f);
    Player_Box.push_back(Player);
}


Player_Sounds::Player_Sounds()
{
    Buffer_jump.loadFromFile("SFX_Jump_09.wav");
    Sound_jump.setBuffer(Buffer_jump);
    Sound_jump.setVolume(60);
    Buffer_run.loadFromFile("step_cloth1.ogg");
    You_say_run.setBuffer(Buffer_run);
    You_say_run.setVolume(80);
    You_say_run.setLoop(true);

}
void Player_Sounds::Sound_movement(int window_value)
{
    if(window_value==6)
    {
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

   dashAnimation.push_back(sf::IntRect(1818, 0, 10, 16));
   dashAnimation.push_back(sf::IntRect(1873, 0, 20, 16));
   dashAnimation.push_back(sf::IntRect(1935, 0, 23, 16));
   dashAnimation.push_back(sf::IntRect(1998, 0, 24, 16));
   dashAnimation.push_back(sf::IntRect(2064, 0, 22, 16));
   dashAnimation.push_back(sf::IntRect(2128, 0, 21, 16));

   RAnimation.push_back(sf::IntRect(11, 10, 126, 138));
   RAnimation.push_back(sf::IntRect(141, 16, 126, 138));
   RAnimation.push_back(sf::IntRect(270, 34, 126, 120));


   wall_grabAnimation= sf::IntRect(1432, 0, 10, 16);

}

sf::IntRect Player_Animation::getCurrentRect(int Current_frame, float Second)
{

    if(dash_pressed)
    {
        std::cout<<Current_frame<<"     "<<dashTime<<"     "<<interval<<std::endl;
        return dashAnimation[Current_frame];
    }
    else if(isJumping && velocity.y<0)
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
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
        return wall_grabAnimation;
    }
    else if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || !(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || !(sf::Keyboard::isKeyPressed(sf::Keyboard::H)))
    {
        return idleAnimation[Current_frame];
    }



}

int Player_Animation ::step(float Second, double animation_fps)
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
int Player_Animation ::Dash()
{



        if(dashTime>interval)
        {




            CurrentDash_frame++;
            interval+=0.095/*39*/;

            if(CurrentDash_frame>5)
            {
                            std::cout<<"dash"<<std::endl;
                CurrentDash_frame=0;
                interval=0.09539;
            }

        }
         return CurrentDash_frame;


}

void Player_Texture::Movement_T(sf::Vector2f position, float Second)
{



        Player_Texture();

        Texture_Box[0].setPosition(position);

        if(dash_pressed)
        {
            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.Dash(), Second));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {

            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 7),Second));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {

            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 14),Second));
            left=0;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {

            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 14),Second));
            left=1;
        }

        else
        {
            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 7),Second));
        }



        if(left)
        {
            Texture_Box[0].setScale(-4,4);
            Texture_Box[0].setPosition(position.x+34.f, position.y);
        }
        if(!left)
        {
            Texture_Box[0].setScale(4,4);
            Texture_Box[0].setPosition(position.x-2.f, position.y);
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

        if(!dash_pressed)
            velocity.x=0.f;
//        velocity.y=0.f;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && dash_pressed==0) {
            velocity.x = -movement_speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && dash_pressed==0) {
            velocity.x = movement_speed;
        }
//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//            velocity.y = movement_speed/2;
//        }

//        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
//            velocity.y = -movement_speed/2;
//        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isJumping==0 && Falling==0)
        {
            velocity.y =jump_speed;

            isJumping=1;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C) && dashTime>1.f)
        {
            if(left) { velocity.x =-1500.f; }
            else { velocity.x =1500.f; }
            dashTime=0;
            dash_pressed=1;
        }
        dashTime+=Second;
            velocity.y += gravity_const;

            if(dash_pressed)
            {
                if(left)
                {
                    velocity.x += 22;
                    if(velocity.x>0)
                        dash_pressed=0;
                }
                else
                {
                    velocity.x -= 22;
                    if(velocity.x<0)
                        dash_pressed=0;
                }

            }


        //std::cout<<velocity.y<<std::endl;


        if (velocity.y>20.f )
        {
            Falling=1;
        }
        Player_Box[0].move(velocity*Second);
    }

}

void Player::Collisions(float Second,int window_value)
{
    if(window_value==6)
    {

        sf::Vector2f reaction;
        sf::FloatRect Player_bounds = Player_Box[0].getGlobalBounds();
        for(auto &i : Collision_Box)
        {


//            std::cout<<"Cokolwiek"<<std::endl;

            sf::Vector2f r =Reaction(i, Player_bounds);
            if(r != sf::Vector2f (0,0))
            {
                if(r.x!=0 && r.y!=0)
                {
                    if(std::abs(r.x)>std::abs(r.y))
                        r.x=0;
                    else
                        r.y=0;
                }
                reaction+=r;

            }

        }


        Player_Box[0].move(reaction);
        if(reaction.y<0)
        {
            velocity.y=0;
            isJumping=0;
            Falling=0;
        }
        if(reaction.y>0)
        {
            velocity.y=0;
        }


    }
}

sf::Vector2f Player::Reaction(sf::FloatRect Platform, sf::FloatRect Player)
{
    bool isIntersecting_top=1;      //top of the platform
    bool isIntersecting_bottom=1;   //bottom of the platform
    bool isIntersecting_left=1;
    bool isIntersecting_right=1;

    if(!Platform.intersects(Player))
    {
        return {};
    }

    //edges check
    if(Platform.top<Player.top)                 //Player below top edge of platform
    {

        isIntersecting_top=0;
    }

    if(Platform.top+Platform.height>Player.top+Player.height)//Player above bottom edge of platform
    {
        isIntersecting_bottom=0;
    }

    if(Platform.left+Platform.width>Player.left+Player.width)//Player on right side of left platform
    {
        isIntersecting_right=0;
    }

    if(Platform.left<Player.left)//Player on left side of right platform
    {
        isIntersecting_left=0;
    }
    //reaction to edges
    sf::Vector2f reaction;
    if(isIntersecting_top && isIntersecting_bottom){}

    else if(isIntersecting_top)
    {
//        std::cout<<"Top"<<std::endl;
        reaction.y = Platform.top-(Player.top+Player.height);
    }
    else if(isIntersecting_bottom)
    {
//        std::cout<<"Bottom"<<std::endl;
        reaction.y = (Platform.top+Platform.height)-Player.top;
    }

    if (isIntersecting_left)
    {
        //std::cout<<"Left"<<std::endl;
        reaction.x = Platform.left-(Player.left+Player.width);
    }
    else if(isIntersecting_right)
    {
        //std::cout<<"right"<<std::endl;
        reaction.x = (Platform.left+Platform.width)-Player.left;
    }

    return reaction;


}

