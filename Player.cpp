#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Map.h>
#include <Colision.h>


Level_Platforms p1;
Level_Walls p2;
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
float Time_after_jump=5.f;
float gravity = gravity_const;
float gravity_falling = gravity_const;

bool Colision_y=0;



void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(Player_Box[0], states);
}

Player::Player()
{
    sf::RectangleShape Player(sf::Vector2f(80.f,80.f));
    Player.setPosition(sf::Vector2f(1200.f,900.f));
    Player_Box.push_back(Player);

}



void Player::Movement(float Second)
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
          //std::cout<<Time_after_jump<<std::endl;
        if(Time_after_jump>0.3)
        {
            std::cout<<"Jump"<<std::endl;
        isJumping=1;
        onFloor=0;
        Time_after_jump=0;
        }
    }


    if(isJumping)
    {


        //std::cout<<gravity<<std::endl;
        Time +=Second;
        gravity +=(gravity_const *Time*Time)/2.f;
        velocity.y +=(jump_speed+ gravity)*Second;

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
                    gravity =0;
                    Time = 0;
                    //Time_after_jump+=Second;
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
                    //Player_Box[0].setPosition(wallBounds.left- PlayerBounds.width, PlayerBounds.top);
                    velocity.x=0.f;
                }

                else if(PlayerBounds.left > wallBounds.left
                        &&  PlayerBounds.left+PlayerBounds.width> wallBounds.left+wallBounds.width
                        &&  PlayerBounds.top< wallBounds.top+wallBounds.height
                        &&  PlayerBounds.top+ PlayerBounds.height> wallBounds.top)

                {
                    //Player_Box[0].setPosition(wallBounds.left+ wallBounds.width, PlayerBounds.top);
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

                else if(PlayerBounds.left > wallBounds.left     //warunek widmo
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
    Time_after_jump+=Second;

}





