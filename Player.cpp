#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <Player.h>
#include <Map.h>
#include <stdlib.h>

Level_Platforms p1;
Player_Animation p3;


float camera_speed=20;
bool P_pressed=0;
bool Free_movement_camera =0;


sf::Vector2f Spawn_position;
std::vector<sf::FloatRect>Collision_Box = p1.PlatformBounds();
std::vector<sf::Vector2f> penetrator_value;
std::vector<bool> penetrator_bool;

bool left=0;
bool already_playing=0;
bool dash_active=0;
bool bar_active=0;
sf::Vector2f bar_speed= (sf::Vector2f(80.f,0));


//Constants
//###################################
const float jump_speed = -1200.f;
const float movement_speed = 400.f;
const float gravity_const = 20.f;
//###################################

sf::Vector2f velocity;
bool why_are_you_running=0;
bool isJumping =0;
bool Falling=0;
bool onFloor =0;
bool double_Jump=0;
bool wall_grab=0;
bool wall_right=0;
bool wall_left=0;
float Time = 0;
float dashTime=12;
float second_jump_Time=1;
float gravity = gravity_const;

bool bruh_wo1=0;
bool bruh_wo2=0;
bool bruh_wo3=0;
bool bruh_wo4=0;

//###########################################################################################################
void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(Player_Box[0], states);
}

Player::Player()
{
    sf::RectangleShape Player(sf::Vector2f(32.f,64.f));
    Player.setPosition(1200.f,900.f);
    Player_Box.push_back(Player);


}

sf::Vector2f Player::getPosition(int number_of_saves, sf::Vector2f Spawn)
{
    if(number_of_saves>0)
        Player_Box[0].setPosition(Spawn);
}

sf::Vector2f Player::Position()
{
    return Player_Box[0].getPosition();
}

sf::FloatRect Player::Player_bounds()
{
    return Player_Box[0].getGlobalBounds();
}

float Player::camera_position(int window_value, float current_position)
{
     sf::Vector2f player_position = Position();
    if(window_value==6)
    {

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        {
            if(!P_pressed)
            {
                P_pressed=1;
                Free_movement_camera=!Free_movement_camera;
            }
        }
        else
            P_pressed=0;

        if(!Free_movement_camera)
        {
            if(player_position.y>650)
                return 540;
            else
                return (player_position.y-100);
        }
        else
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                return current_position +camera_speed;
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                return current_position-camera_speed;
            }
            else
                return current_position;
        }
    }


}

void Player::Movement(float Second, int window_value, std::vector<bool> abilities)
{
    if(window_value==6)
    {
        dashTime+=Second;
        second_jump_Time+=Second;

        if(!dash_active)
            velocity.x=0.f;

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && dash_active==0) {
            velocity.x = -movement_speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D) && dash_active==0) {
            velocity.x = movement_speed;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isJumping==0 && Falling==0)
        {
            velocity.y =jump_speed;
            second_jump_Time=0;
            isJumping=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isJumping==1 && double_Jump==0 && second_jump_Time>0.4 && abilities[1])
        {
            velocity.y =jump_speed;

            double_Jump=1;
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::C) && dashTime>5.f && abilities[2])
        {
            if(left) { velocity.x =-1500.f; }
            else { velocity.x =1500.f; }
            dashTime=0;
            dash_active=1;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F) && (wall_right==1 || wall_left==1) && abilities[3])
        {
            velocity.x=0;
            velocity.y=0;
            wall_grab=1;

        }
        else
        {
            wall_grab=0;
        }

        if(velocity.y>3000.f){
            velocity.y=3000.f;
        }
        else{
            velocity.y += gravity_const;
        }


        if(dash_active)
        {
            if(left)
            {
                velocity.x += 22;
                if(velocity.x>0)
                    dash_active=0;
            }
            else
            {
                velocity.x -= 22;
                if(velocity.x<0)
                    dash_active=0;
            }

        }

        if (velocity.y>20.f )
        {
            Falling=1;
        }
        Player_Box[0].move(velocity*Second);
    }

}

void Player::Collisions(int window_value)
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
            double_Jump=0;
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
        wall_right=0;
        wall_left=0;

        isIntersecting_top=0;
    }

    if(Platform.top+Platform.height>Player.top+Player.height)//Player above bottom edge of platform
    {
        wall_right=0;
        wall_left=0;
        isIntersecting_bottom=0;
    }

    if(Platform.left+Platform.width>Player.left+Player.width)//Player on right side of left platform
    {
        wall_left=0;
        isIntersecting_right=0;
    }

    if(Platform.left<Player.left)//Player on left side of right platform
    {
        wall_right=0;

        isIntersecting_left=0;
    }
    //reaction to edges
    sf::Vector2f reaction;

    if (isIntersecting_left)
    {
       // std::cout<<"Left"<<std::endl;
        wall_right=1;
        reaction.x = Platform.left-(Player.left+Player.width);
    }
    else if(isIntersecting_right)
    {
        //std::cout<<"right"<<std::endl;
        wall_left=1;
        reaction.x = (Platform.left+Platform.width)-Player.left;
    }

    if(isIntersecting_top && isIntersecting_bottom){}

    else if(isIntersecting_top)
    {
//        std::cout<<"Top"<<std::endl;
        wall_right=0;
        wall_left=0;
        reaction.y = Platform.top-(Player.top+Player.height);
    }
    else if(isIntersecting_bottom)
    {
//        std::cout<<"Bottom"<<std::endl;
        wall_right=0;
        wall_left=0;
        reaction.y = (Platform.top+Platform.height)-Player.top;
    }



    return reaction;


}



//###########################################################################################################
void Player_Animation::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(bruh_wo3)
    {
    target.draw(dash_bar, states);
    target.draw(dash_outline1, states);
    target.draw(dash_outline2, states);
    target.draw(dash_outline3, states);
    target.draw(dash_outline4, states);
    }


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

   dash_outline1.setSize(sf::Vector2f(10.f, 80.f));
   dash_outline2.setSize(sf::Vector2f(400.f, 10.f));
   dash_outline3.setSize(sf::Vector2f(10.f, 80.f));
   dash_outline4.setSize(sf::Vector2f(400.f, 10.f));

   dash_bar.setSize(sf::Vector2f(400.f, 80.f));

   dash_outline1.setFillColor(sf::Color(160, 122, 214));
   dash_outline2.setFillColor(sf::Color(160, 122, 214));
   dash_outline3.setFillColor(sf::Color(160, 122, 214));
   dash_outline4.setFillColor(sf::Color(160, 122, 214));
   dash_bar.setFillColor(sf::Color(255,0,0));



}

sf::IntRect Player_Animation::getCurrentRect(int Current_frame)
{
    if(wall_grab)
    {
        return wall_grabAnimation;
    }
    if(dash_active)
    {
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


    if(dash_active && (velocity.x>1200.f || velocity.x<-1200.f))
    {
        CurrentDash_frame=0;
    }
    if(dash_active && ((velocity.x>800.f && velocity.x<1200.f) || (velocity.x<-800.f && velocity.x>-1200.f)))
    {
        CurrentDash_frame=1;
    }
    if(dash_active && ((velocity.x>600.f && velocity.x<800.f) || (velocity.x<-600.f && velocity.x>-800.f)))
    {
        CurrentDash_frame=2;
    }
    if(dash_active && ((velocity.x>400.f && velocity.x<600.f) || (velocity.x<-400.f && velocity.x>-600.f)))
    {
        CurrentDash_frame=3;
    }
    if(dash_active && ((velocity.x>200.f && velocity.x<400.f) || (velocity.x<-200.f && velocity.x>-400.f)))
    {
        CurrentDash_frame=4;
    }
    if(dash_active && ((velocity.x<200.f && velocity.x>0.f)|| (velocity.x>-200.f && velocity.x<0.f)))
    {
        CurrentDash_frame=5;
    }
    return CurrentDash_frame;


}

void Player_Animation::dash_bar_animation(float Position, float Second)
{

    dash_outline1.setPosition(0.f, Position-540.f);
    dash_outline2.setPosition(0.f, Position-540.f);
    dash_outline3.setPosition(390.f, Position-540.f);
    dash_outline4.setPosition(0.f, Position-470.f);

    if(bar_active)
    {

        if(dash_bar.getGlobalBounds().left>0)
        {
            bar_active=0;
        }
        else
        {
            dash_bar.move(bar_speed*Second);
            dash_bar.setPosition(dash_bar.getPosition().x,Position-540.f);
        }


    }
    else
    {

        dash_bar.setPosition(0.f,Position-540.f);
    }

    if(dash_active)
    {
        if(!bar_active)
        {
            bar_active=1;
           dash_bar.setPosition(-400.f,Position-540.f);

        }



    }

}
//###########################################################################################################
void Player_Texture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(Texture_Box[0], states);
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

void Player_Texture::Movement_T(sf::Vector2f position, float Second)
{



        Player_Texture();

        if(dash_active)
        {
            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.Dash()));

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {

            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 7)));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {

            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 14)));
            left=0;
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {

            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 14)));
            left=1;
        }

        else
        {
            Texture_Box[0].setTextureRect(animation.getCurrentRect(animation.step(Second, 7)));
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


//###########################################################################################################
Player_Sounds::Player_Sounds()
{
    Buffer_jump.loadFromFile("SFX_Jump_09.wav");
    Sound_jump.setBuffer(Buffer_jump);
    Sound_jump.setVolume(60);

    Buffer_double_jump.loadFromFile("SFX_Jump_42.wav");
    Sound_Double_jump.setBuffer(Buffer_double_jump);
    Sound_Double_jump.setVolume(60);

    Bruh_buffer.loadFromFile("Bruh Sound Effect #2.ogg");
    Bruh_sound.setBuffer(Bruh_buffer);
    Bruh_sound.setVolume(120);

    yamete_buffer.loadFromFile("Yamete kudasai sound effect.ogg");
    yamete_sound.setBuffer(yamete_buffer);
    yamete_sound.setVolume(120);




    Buffer_run.loadFromFile("step_cloth1.ogg");
    You_say_run.setBuffer(Buffer_run);
    You_say_run.setVolume(80);
    You_say_run.setLoop(true);

}

void Player_Sounds::Sound_movement(int window_value, std::vector<bool> bruh)
{
    if(window_value==6)
    {

        //std::cout<<bruh_wo1<<"   "<<bruh_wo2<<"   "<<bruh_wo3<<"   "<<bruh_wo4<<"   "<<std::endl;

        if(bruh[0])
        {
            if(!bruh_wo1)
            {
                Bruh_sound.setPlayingOffset(sf::seconds(0.5));
            Bruh_sound.play();
            bruh_wo1=1;
            }
        }
        if(bruh[1])
        {
            if(!bruh_wo2)
            {
                Bruh_sound.setPlayingOffset(sf::seconds(0.5));
            Bruh_sound.play();
            bruh_wo2=1;
            }
        }
        if(bruh[2])
        {
            if(!bruh_wo3)
            {
                Bruh_sound.setPlayingOffset(sf::seconds(0.5));
            Bruh_sound.play();
            bruh_wo3=1;
            }
        }
        if(bruh[3])
        {
            if(!bruh_wo4)
            {
                Bruh_sound.setPlayingOffset(sf::seconds(0.5));
            Bruh_sound.play();
            bruh_wo4=1;
            }
        }

     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& isJumping==0 && Falling==0)
     {
         Sound_jump.play();
     }
     if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && isJumping==1 && double_Jump==0 && second_jump_Time>0.39 && bruh[1])
     {
         Sound_Double_jump.play();
     }
     if((sf::Keyboard::isKeyPressed(sf::Keyboard::A) && isJumping==0 && Falling==0)||( sf::Keyboard::isKeyPressed(sf::Keyboard::D) && isJumping==0 && Falling==0) )
     {

         why_are_you_running=1;
     }
     else if(!(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) || !(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || isJumping==1  || Falling==1)
     {
         why_are_you_running=0;
     }

     if(why_are_you_running && !dash_active)
     {
        if(!already_playing)
        {
           You_say_run.play();
           already_playing=1;
        }

     }
     else if(!why_are_you_running || dash_active)
     {
         You_say_run.pause();
         already_playing=0;
     }



    }
}

void Player_Sounds::reset()
{
    bruh_wo1=0;
    bruh_wo2=0;
    bruh_wo3=0;
    bruh_wo4=0;
}

void Player_Sounds::file_exist(std::vector<bool> chests)
{
    if(chests[0])
        bruh_wo1=1;
    else
       bruh_wo1=0;
    if(chests[1])
        bruh_wo2=1;
    else
       bruh_wo2=0;
    if(chests[2])
        bruh_wo3=1;
    else
       bruh_wo3=0;
    if(chests[3])
        bruh_wo4=1;
    else
       bruh_wo4=0;

}

//###########################################################################################################

