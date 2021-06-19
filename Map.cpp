#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Map.h>
#include <Colision.h>
#include <string>
#include <fstream>



//int screen_width;
//int screen_height;
double scale_factor;
bool chest1_open=0;
bool chest2_open=0;
bool chest3_open=0;

bool fresh_file=1;
int Tutorial_part=1;
bool already_preesed=0;

bool D_jump=0;
bool dash_ability=0;
bool wall_climb=0;







//###########################################################################################################
float Time_k=0;

Tutorial::Tutorial()
{

    keyAnimation.push_back(sf::IntRect(11, 10, 125, 150));
    keyAnimation.push_back(sf::IntRect(141, 10, 125, 150));
    keyAnimation.push_back(sf::IntRect(270, 10, 125, 150));
}
sf::IntRect Tutorial::getCurrentRect(int Current_frame, float Second)
{

        return keyAnimation[Current_frame];

}
int Tutorial ::step(float Second, double animation_fps)
{
        float time_between_frames=1.f/animation_fps;


        Time_k = Time_k + Second;


        if(Time_k>time_between_frames)
        {
            Current_frame++;
            Time_k= Time_k- time_between_frames;
            if(Current_frame ==3)//frames.size())
            {
                Current_frame=0;
            }
        }

        return Current_frame;
}



//###########################################################################################################
void Map_Texture::draw(sf::RenderTarget &target, sf::RenderStates states) const
{


    target.draw(Texture_Box[0],states);
    target.draw(Texture_Box[1],states);
    target.draw(Texture_Box[2],states);
    if(fresh_file)
    {
        if(Tutorial_part==1)
        {
            target.draw(Black_Background,states);
            target.draw(Texture_Box[7],states);
            target.draw(Texture_Box[9],states);
            target.draw(Tutorial1_1,states);
            target.draw(Tutorial1_2,states);
            target.draw(Tutorial1_3,states);
            target.draw(Tutorial1_4,states);
        }
//        if(Tutorial_part==2)
//        {

//        }





        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            if(!already_preesed)
            {
            Tutorial_part++;
            already_preesed=1;
            }
        }
        else
            already_preesed=0;
        //std::cout<<Tutorial_part<<std::endl;


    }


}

Map_Texture::Map_Texture()
{

    font.loadFromFile("OpenSans-Bold.ttf");
    Tutorial1_1.setFont(font);
    Tutorial1_2.setFont(font);
    Tutorial1_3.setFont(font);
    Tutorial1_4.setFont(font);

    Tutorial1_1.setCharacterSize(55);
    Tutorial1_2.setCharacterSize(55);
    Tutorial1_3.setCharacterSize(55);
    Tutorial1_4.setCharacterSize(25);

    Tutorial1_1.setFillColor(sf::Color::White);
    Tutorial1_2.setFillColor(sf::Color::White);
    Tutorial1_3.setFillColor(sf::Color::White);
    Tutorial1_4.setFillColor(sf::Color::White);

    Tutorial1_1.setString("Hello traveler,");
    Tutorial1_2.setString("To move left press:");
    Tutorial1_3.setString("and to move right press: ");
    Tutorial1_4.setString("Press ENTER to continue or M to skip all tutorials");


    Black_Background.setSize(sf::Vector2f(1520.f,500.f));
    Black_Background.setFillColor(sf::Color (89,84,84));



    Chest_Texture.loadFromFile("Chest.png");
    Door_Texture.loadFromFile("Door.png");
    W_Texture.loadFromFile("W.png");
    E_Texture.loadFromFile("E.png");
    R_Texture.loadFromFile("R.png");
    A_Texture.loadFromFile("A.png");
    S_Texture.loadFromFile("S.png");
    D_Texture.loadFromFile("D.png");
    F_Texture.loadFromFile("F.png");
    C_Texture.loadFromFile("C.png");


    Chest1.setTexture(Chest_Texture);
    Chest2.setTexture(Chest_Texture);
    Chest3.setTexture(Chest_Texture);
    Door.setTexture(Door_Texture);
    W.setTexture(W_Texture);
    E.setTexture(E_Texture);
    R.setTexture(R_Texture);
    A.setTexture(A_Texture);
    S.setTexture(S_Texture);
    D.setTexture(D_Texture);
    F.setTexture(F_Texture);
    C.setTexture(C_Texture);

    Texture_Box.push_back(Chest1);  //0
    Texture_Box.push_back(Chest2);  //1
    Texture_Box.push_back(Chest3);  //2
    Texture_Box.push_back(Door);    //3
    Texture_Box.push_back(W);       //4
    Texture_Box.push_back(E);       //5
    Texture_Box.push_back(R);       //6
    Texture_Box.push_back(A);       //7
    Texture_Box.push_back(S);       //8
    Texture_Box.push_back(D);       //9
    Texture_Box.push_back(F);       //10
    Texture_Box.push_back(C);       //11


    Chest_Position.push_back(sf::IntRect(0, 0, 254, 254));
    Chest_Position.push_back(sf::IntRect(256, 0, 254, 254));

    Texture_Box[0].setTextureRect(Chest_Position[0]);
    Texture_Box[1].setTextureRect(Chest_Position[0]);
    Texture_Box[2].setTextureRect(Chest_Position[0]);


    Texture_Box[0].setScale(0.35,0.35);
    Texture_Box[1].setScale(0.35,0.35);
    Texture_Box[2].setScale(0.35,0.35);


    Texture_Box[0].setPosition(sf::Vector2f(350.f,931.f));
    Texture_Box[1].setPosition(sf::Vector2f(800.f,291.f));
    Texture_Box[2].setPosition(sf::Vector2f(400.f,-89.f));
}

void Map_Texture::key_animation(float Second, float camera)
{

    sf::IntRect amimation_frame =animation.getCurrentRect(animation.step(Second, 3), Second);

    Tutorial1_1.setPosition(250,camera-400.f);
    Tutorial1_2.setPosition(250,camera-250.f);
    Tutorial1_3.setPosition(250,camera-100.f);
    Tutorial1_4.setPosition(1100,camera+5.f);
    Black_Background.setPosition(200.f, camera-450.f);

    Texture_Box[7].setPosition(950.f,camera-280.f);
    Texture_Box[7].setTextureRect(amimation_frame);

    Texture_Box[9].setPosition(950.f,camera-130.f);
    Texture_Box[9].setTextureRect(amimation_frame);

//    Texture_Box[6].setPosition(900.f,500.f);
//    Texture_Box[6].setTextureRect(amimation_frame);
}

void Map_Texture::placement(sf::FloatRect Player_Bounds)
{
    if(Texture_Box[0].getGlobalBounds().intersects(Player_Bounds))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
                Texture_Box[0].setTextureRect(Chest_Position[1]);
                chest1_open=1;
                D_jump=1;
        }
    }
    if(Texture_Box[1].getGlobalBounds().intersects(Player_Bounds))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
                Texture_Box[1].setTextureRect(Chest_Position[1]);
                chest2_open=1;
                dash_ability=1;
        }
    }
    if(Texture_Box[2].getGlobalBounds().intersects(Player_Bounds))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
                Texture_Box[2].setTextureRect(Chest_Position[1]);
                chest3_open=1;
                wall_climb=1;
        }
    }


}

std::vector<bool> Map_Texture::is_chest_open()
{
    std::vector<bool>chest_open;
    chest_open.push_back(chest1_open);
    chest_open.push_back(chest2_open);
    chest_open.push_back(chest3_open);

    return chest_open;
    chest_open.clear();

}

void Map_Texture::is_this_fresh_file(bool it_is)
{
    if(it_is)
       fresh_file=1;
    else
        fresh_file=0;
}

std::vector<bool> Map_Texture::abilities()
{
    abilities_bool.push_back(D_jump);
    abilities_bool.push_back(dash_ability);
    abilities_bool.push_back(wall_climb);
}
//###########################################################################################################
float grid_size=60.f;
void Level_Platforms::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for(int i=0; i<single_platform.size(); i++)
    {
        target.draw(single_platform[i],states);
    }

}

Level_Platforms::Level_Platforms()
{
    Walls_Texture.loadFromFile("Test.png");
    Walls_Texture.setRepeated(true);
    int elements_pushed=0;

    sf::RectangleShape Platform (sf::Vector2f(grid_size,grid_size));

    map.open("map.txt");
    bool linia ;
    std::vector <bool> platforms;

    while(map>>linia)
    {
       platforms.push_back(linia) ;
    }

    for(int i=0; i<platforms.size(); i+=32)
    {

        for(int x=0; x<32; x++)
        {
            if(platforms[i+x])
            {

                single_platform.push_back(Platform);
                single_platform[elements_pushed].setPosition(x*grid_size,((i/(-32))*grid_size)+1020.f);
                single_platform[elements_pushed].setTexture(&Walls_Texture);
                single_platform[elements_pushed].setTextureRect(sf::IntRect(0, 0,grid_size,grid_size));
                elements_pushed++;


            }

        }
    }

    map.close();

    sf::RectangleShape Floor (sf::Vector2f(30*grid_size,grid_size));
    Floor.setPosition(grid_size,17*grid_size);
    Floor.setTexture(&Walls_Texture);
    Floor.setTextureRect(sf::IntRect(0, 0, 30*grid_size,grid_size));

    sf::RectangleShape Wall_left (sf::Vector2f(grid_size,64*grid_size));
    Wall_left.setPosition(0,-1000.f);
    Wall_left.setTexture(&Walls_Texture);
    Wall_left.setTextureRect(sf::IntRect(0, 0, grid_size,64*grid_size));

    sf::RectangleShape Wall_right (sf::Vector2f(grid_size,64*grid_size));
    Wall_right.setPosition(1860.f,-1000.f);
    Wall_right.setTexture(&Walls_Texture);
    Wall_right.setTextureRect(sf::IntRect(0, 0, grid_size,64*grid_size));


    single_platform.push_back(Floor);
    single_platform.push_back(Wall_left);
    single_platform.push_back(Wall_right);


}

std::vector<sf::FloatRect> Level_Platforms::PlatformBounds()
{
    std::vector<sf::FloatRect> CakeIsALie{};
    for(auto &i : single_platform)
    {
        sf::FloatRect wallBounds = i.getGlobalBounds();
        CakeIsALie.push_back(wallBounds);
    }
    return CakeIsALie;
}



//###########################################################################################################
void BackGround::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(BackGround_T);
}

BackGround::BackGround()
{
    BackGround_Texture.loadFromFile("Wall2.png");
    BackGround_Texture.setRepeated(true);
    BackGround_T.setTexture(BackGround_Texture);
    BackGround_T.setTextureRect(sf::IntRect(0, 0, 1920, 2080));
    BackGround_T.setPosition(0,-1000);
}

