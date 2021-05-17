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
std::vector<sf::FloatRect>WallBounds = p2.WallBound();



//Gravity
//float jump_speed = -2200.f;
//const float gravity_const = 20.f;
//bool isJumping =0;
//bool onFloor =0;
//float Time = 0;
//float gravity;

//bool Colision_y=0;



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

    float movement_speed = 400.f;



    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x += -movement_speed*Second;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x += movement_speed*Second;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        velocity.y += movement_speed*Second;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y += -movement_speed*Second;
    }


    Player_Box[0].move(velocity);

    //Wall colision
    for(auto &i : WallBounds)
    {
        sf::FloatRect PlayerBounds = Player_Box[0].getGlobalBounds();

        //Left collision
    if(PlayerBounds.left< i.left+i.width)
        Player_Box[0].setPosition(i.left+i.width, Player_Box[0].getPosition().y);
//        //Right collision
//    else if(Player_Box[0].getPosition().x> i.left)
//        Player_Box[0].setPosition(i.left, Player_Box[0].getPosition().y);
//        //Bottom collision
//    else if(Player_Box[0].getPosition().y>i.top)
//        Player_Box[0].setPosition(Player_Box[0].getPosition().x,i.top);
    }


    std::cout<<Player_Box[0].getPosition().x<<"    "<<Player_Box[0].getPosition().y<<std::endl;















































//    if(isJumping==1)
//    {
//        Time +=Second;
//        gravity +=(gravity_const *Time*Time)/2;




//         velocity.y += (jump_speed+gravity_const)*Second;


//        for(auto &i : GroudBounds){
//            sf::FloatRect playerBounds = Player_Box[0].getGlobalBounds();
//            sf::FloatRect wallBounds = i;
//            GroundDetection= playerBounds;
//            GroundDetection.left += velocity.x;
//            GroundDetection.top += velocity.y;

//            if(wallBounds.intersects(GroundDetection))
//            {

//                if(playerBounds.top < wallBounds.top
//                        &&  playerBounds.top+playerBounds.height< wallBounds.top+wallBounds.height
//                        /*&&  playerBounds.left< wallBounds.left+wallBounds.width
//                        &&  playerBounds.left+ playerBounds.width> wallBounds.left*/)
//                std::cout<<"Przed  "<<Player_Box[0].getPosition().y<<std::endl;
//                if(playerBounds.top+playerBounds.height> wallBounds.top)
//                {
//                    if(!Colision_y)
//                    {
//                        Colision_y=true;
//                        std::cout<<"Gowno"<<std::endl;

//                        isJumping=0;
//                        onFloor=1;
//                        gravity =0;
//                        Time = 0;
//                        velocity.y=0.f;
//                        Player_Box[0].setPosition(Player_Box[0].getPosition().x, wallBounds.top- playerBounds.height-50);
//                    }


//                }


//                //                else if(playerBounds.top > wallBounds.top
//                        &&  playerBounds.top+playerBounds.height> wallBounds.top+wallBounds.height
//                        )
//                else if(playerBounds.top< wallBounds.top+wallBounds.height)
//                {
//                    velocity.y= 0.f ;
//                    Player_Box[0].setPosition(Player_Box[0].getPosition().x, wallBounds.top+ wallBounds.height);

//                }

//                else if (playerBounds.left+playerBounds.width>wallBounds.left)
//                {
//                    velocity.x=0.f;
//                    Player_Box[0].setPosition(wallBounds.left, Player_Box[0].getPosition().y);
//                    onFloor=0;
//                }
//                else if (playerBounds.left<wallBounds.left+wallBounds.width)
//                {
//                    velocity.x=0.f;
//                    Player_Box[0].setPosition(wallBounds.left+wallBounds.width, Player_Box[0].getPosition().y);
//                    onFloor=0;
//                }
//            }
//            else Colision_y =0, onFloor =0;

//        }
//    }

//    if(onFloor==0)
//    {

//        Time +=Second;
//        gravity +=(gravity_const  *Time*Time)/2;

//        velocity.y += (gravity)*Second;

//        for(auto &i : GroudBounds){
//            sf::FloatRect playerBounds = Player_Box[0].getGlobalBounds();
//            sf::FloatRect wallBounds = i;
//            GroundDetection= playerBounds;
//            GroundDetection.left += velocity.x;
//            GroundDetection.top += velocity.y;

//            if(wallBounds.intersects(GroundDetection))
//            {

//                if(playerBounds.top < wallBounds.top
//                        &&  playerBounds.top+playerBounds.height< wallBounds.top+wallBounds.height
//                        /*&&  playerBounds.left< wallBounds.left+wallBounds.width
//                       &&  playerBounds.left+ playerBounds.width> wallBounds.left*/)
//                if(playerBounds.top+playerBounds.height> wallBounds.top)
//                {
//                    if(!Colision_y)
//                    {
//                        Colision_y=true;

//                        isJumping=0;
//                        onFloor=1;
//                        gravity =0;
//                        Time = 0;
//                        velocity.y=0.f;
//                        Player_Box[0].setPosition(Player_Box[0].getPosition().x, wallBounds.top-playerBounds.height);
//                    }

//                }
//                else if(playerBounds.top > wallBounds.top
//                        &&  playerBounds.top+playerBounds.height> wallBounds.top+wallBounds.height
//                        )
//                else if(playerBounds.top< wallBounds.top+wallBounds.height)
//                {
//                    velocity.y= 0.f ;
//                    Player_Box[0].setPosition(Player_Box[0].getPosition().x, wallBounds.top+ wallBounds.height);

//                }

//                else if (playerBounds.left+playerBounds.width>wallBounds.left)
//                {
//                    velocity.x=0.f;
//                    Player_Box[0].setPosition(wallBounds.left, Player_Box[0].getPosition().y);
//                    onFloor=0;
//                }
//                else if (playerBounds.left<wallBounds.left+wallBounds.width)
//                {
//                    velocity.x=0.f;
//                    Player_Box[0].setPosition(wallBounds.left+wallBounds.width, Player_Box[0].getPosition().y);
//                    onFloor=0;
//                }
//            }


//            else Colision_y =0, onFloor =0;


//        }
//    }








//        sf::FloatRect NextPos;

//        for(auto &i : GroudBounds)
//        {
//            sf::FloatRect playerBounds = Player_Box[0].getGlobalBounds();
//            sf::FloatRect wallBounds = i;
//            NextPos= playerBounds;
//            NextPos.left += velocity.x;
//            NextPos.top += velocity.y;

//            if(wallBounds.intersects(NextPos))
//            {
//                if(playerBounds.left < wallBounds.left
//                        &&  playerBounds.left+playerBounds.width< wallBounds.left+wallBounds.width)
//                {
//                    velocity.x=0.f;
//                    Player_Box[0].setPosition(wallBounds.left- playerBounds.width, playerBounds.top);

//                }

//                else if(playerBounds.left > wallBounds.left
//                        &&  playerBounds.left+playerBounds.width> wallBounds.left+wallBounds.width)

//                {
//                    velocity.x=0.f;
//                    Player_Box[0].setPosition(wallBounds.left+ wallBounds.width, playerBounds.top);

//                }
//            }
//        }


}





