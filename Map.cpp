#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <Player.h>
#include <Map.h>
#include <string>
#include <fstream>


double scale_factor;
bool chest1_open=0;
bool chest2_open=0;
bool chest3_open=0;
bool chest4_open=0;


bool chest1_open_lastframe=0;
bool chest2_open_lastframe=0;
bool chest3_open_lastframe=0;
bool chest4_open_lastframe=0;

bool window_open=0;

bool fresh_file=1;
int Tutorial_part=1;
bool already_preesed=0;

//###########################################################################################################
float Time_k=0;

Tutorial::Tutorial()
{

    keyAnimation.push_back(sf::IntRect(11, 10, 125, 150));
    keyAnimation.push_back(sf::IntRect(141, 10, 125, 150));
    keyAnimation.push_back(sf::IntRect(270, 10, 125, 150));
}
sf::IntRect Tutorial::getCurrentRect(int Current_frame)
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
            if(Current_frame ==3)
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
    target.draw(Texture_Box[3],states);
    if(fresh_file)
    {
        if(Tutorial_part==1)
        {

            target.draw(Pop_up_window,states);
            target.draw(Texture_Box[7],states);
            target.draw(Texture_Box[9],states);
            target.draw(Tutorial1_1,states);
            target.draw(Tutorial1_2,states);
            target.draw(Tutorial1_3,states);
            target.draw(Tutorial1_4,states);
            window_open=1;
        }
        if(Tutorial_part==2)
        {
            target.draw(Pop_up_window,states);
            target.draw(Texture_Box[5],states);
            target.draw(Tutorial1_1,states);
            target.draw(Tutorial1_2,states);
            target.draw(Tutorial1_3,states);
            target.draw(Tutorial1_4,states);
            window_open=1;


        }

        if(chest1_open && !chest1_open_lastframe)
        {
            if(!window_open)
            {
            Tutorial_part=4;
            window_open=1;
            }
        }
        if(chest2_open && !chest2_open_lastframe )
        {
            if(!window_open)
            {
            Tutorial_part=6;
            window_open=1;
            }
        }
        if(chest3_open && !chest3_open_lastframe)
        {
            if(!window_open)
            {
            Tutorial_part=8;
            window_open=1;
            }
        }
        if(chest4_open && !chest4_open_lastframe)
        {
            if(!window_open)
            {
            Tutorial_part=10;
            window_open=1;
            }
        }
        if(Tutorial_part==4)
        {
           target.draw(Pop_up_window,states);
           target.draw(Tutorial1_1,states);
           target.draw(Tutorial1_2,states);
           target.draw(Tutorial1_4,states);

        }
        if(Tutorial_part==6)
        {
           target.draw(Pop_up_window,states);
           target.draw(Tutorial1_1,states);
           target.draw(Tutorial1_2,states);
           target.draw(Tutorial1_3,states);
           target.draw(Tutorial1_4,states);



        }
        if(Tutorial_part==8)
        {
           target.draw(Pop_up_window,states);
           target.draw(Tutorial1_1,states);
           target.draw(Tutorial1_2,states);
           target.draw(Tutorial1_4,states);
           target.draw(Texture_Box[11],states);


        }
        if(Tutorial_part==10)
        {
           target.draw(Pop_up_window,states);
           target.draw(Tutorial1_1,states);
           target.draw(Tutorial1_2,states);
           target.draw(Tutorial1_4,states);
           target.draw(Texture_Box[10],states);


        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && window_open)
        {
            if(!already_preesed)
            {
            Tutorial_part++;
             window_open=0;
            already_preesed=1;
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::M) )
        {
            if(!already_preesed)
            {
            Tutorial_part=20;
            window_open=0;
            already_preesed=1;
            }
        }
        else
            already_preesed=0;
//        std::cout<<Tutorial_part<<std::endl;


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



    Pop_up.loadFromFile("Pop_up.png");
    Pop_up_window.setTexture(Pop_up);
//    Black_Background.setSize(sf::Vector2f(1520.f,500.f));
//    Black_Background.setFillColor(sf::Color (89,84,84));



    Chest_Texture.loadFromFile("Chest_press2.png");
    Door_Texture.loadFromFile("Door.png");
    E_Texture.loadFromFile("E.png");
    R_Texture.loadFromFile("R.png");
    A_Texture.loadFromFile("A.png");
    S_Texture.loadFromFile("S.png");
    D_Texture.loadFromFile("D.png");
    F_Texture.loadFromFile("F.png");
    C_Texture.loadFromFile("C.png");


    Chest.setTexture(Chest_Texture);

    Door.setTexture(Door_Texture);
    E.setTexture(E_Texture);
    R.setTexture(R_Texture);
    A.setTexture(A_Texture);
    S.setTexture(S_Texture);
    D.setTexture(D_Texture);
    F.setTexture(F_Texture);
    C.setTexture(C_Texture);




    Chest_Position.push_back(sf::IntRect(0, 236, 254, 274));
    Chest_Position.push_back(sf::IntRect(256, 236, 254, 274));


    int elements_pushed=0;
    float grid_size=60.f;
    map.open("map.txt");
    int linia ;
    std::vector <int> platforms;

    while(map>>linia)
    {
       platforms.push_back(linia) ;
    }

    for(int i=0; i<platforms.size(); i+=32)
    {

        for(int x=0; x<32; x++)
        {
            if(platforms[i+x]==2)
            {

                Texture_Box.push_back(Chest);
                Texture_Box[elements_pushed].setPosition(x*grid_size,((i/(-32))*grid_size)+985.f);
                Texture_Box[elements_pushed].setScale(0.35,0.35);
                Texture_Box[elements_pushed].setTextureRect(Chest_Position[0]);
                elements_pushed++;
            }

        }
    }

    map.close();


    Texture_Box.push_back(Door);    //4
    Texture_Box.push_back(E);       //5
    Texture_Box.push_back(R);       //6
    Texture_Box.push_back(A);       //7
    Texture_Box.push_back(S);       //8
    Texture_Box.push_back(D);       //9
    Texture_Box.push_back(F);       //10
    Texture_Box.push_back(C);       //11



}

void Map_Texture::key_animation(float Second, float camera)
{

    sf::IntRect amimation_frame =animation.getCurrentRect(animation.step(Second, 3));

    Tutorial1_4.setString("Press ENTER to continue or M to skip all tutorials");
    if(Tutorial_part==1)
    {
        Tutorial1_1.setString("Hello traveler,");
        Tutorial1_2.setString("To move left press:");
        Tutorial1_3.setString("and to move right press: ");

    }
    if(Tutorial_part==2)
    {
        Tutorial1_1.setString("To jump press spacebar");
        Tutorial1_2.setString("and to interact press:");
        Tutorial1_3.setString("Look a chest, open it! ");
    }
    if(Tutorial_part==4)
    {
        Tutorial1_1.setString("Unfortunately this chest is empty");
        Tutorial1_2.setString("Maybe next one will have someting exciting inside");

    }

    if(Tutorial_part==6)
    {
        Tutorial1_1.setString("Double jump?");
        Tutorial1_2.setString("Amazing");
        Tutorial1_3.setString("By pressing spacebar in mid air you can jump again");
    }

    if(Tutorial_part==8)
    {
        Tutorial1_1.setString("Dashing ability, it sure will come in handy");
        Tutorial1_2.setString("To dash press: ");

    }

    if(Tutorial_part==10)
    {
        Tutorial1_1.setString("Thanks to content of this chest you can hold onto walls");
        Tutorial1_2.setString("To hold onto wall press and hold: ");

    }


    Tutorial1_1.setPosition(250,camera-470.f);
    Tutorial1_2.setPosition(250,camera-320.f);
    Tutorial1_3.setPosition(250,camera-170.f);
    Tutorial1_4.setPosition(1100,camera-65.f);
    Pop_up_window.setPosition(140.f, camera-540.f);

    Texture_Box[7].setPosition(950.f,camera-350.f);
    Texture_Box[7].setTextureRect(amimation_frame);

    Texture_Box[9].setPosition(950.f,camera-200.f);
    Texture_Box[9].setTextureRect(amimation_frame);

    Texture_Box[5].setPosition(950.f,camera-350.f);
    Texture_Box[5].setTextureRect(amimation_frame);

    Texture_Box[11].setPosition(800.f,camera-350.f);
    Texture_Box[11].setTextureRect(amimation_frame);

    Texture_Box[10].setPosition(1150.f,camera-350.f);
    Texture_Box[10].setTextureRect(amimation_frame);


}

void Map_Texture::placement(sf::FloatRect Player_Bounds)
{

    chest1_open_lastframe=chest1_open;
    chest2_open_lastframe=chest2_open;
    chest3_open_lastframe=chest3_open;
    chest4_open_lastframe=chest4_open;

    if(Texture_Box[0].getGlobalBounds().intersects(Player_Bounds))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {

                chest1_open=1;

        }
    }
    if(Texture_Box[1].getGlobalBounds().intersects(Player_Bounds))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {

                chest2_open=1;
        }
    }
    if(Texture_Box[2].getGlobalBounds().intersects(Player_Bounds))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {

                chest3_open=1;
        }
    }
    if(Texture_Box[3].getGlobalBounds().intersects(Player_Bounds))
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {

                chest4_open=1;
        }
    }


    if(chest1_open)
    {
        Texture_Box[0].setTextureRect(Chest_Position[1]);
    }
    else
    {
        Texture_Box[0].setTextureRect(Chest_Position[0]);
    }
    if(chest2_open)
    {
       Texture_Box[1].setTextureRect(Chest_Position[1]);
    }
    else
    {
        Texture_Box[1].setTextureRect(Chest_Position[0]);
    }
    if(chest3_open)
    {
        Texture_Box[2].setTextureRect(Chest_Position[1]);
    }
    else
    {
        Texture_Box[2].setTextureRect(Chest_Position[0]);
    }
    if(chest4_open)
    {
        Texture_Box[3].setTextureRect(Chest_Position[1]);
    }
    else
    {
        Texture_Box[3].setTextureRect(Chest_Position[0]);
    }




}

std::vector<bool> Map_Texture::is_chest_open()
{
    std::vector<bool>chest_open;
    chest_open.push_back(chest1_open);
    chest_open.push_back(chest2_open);
    chest_open.push_back(chest3_open);
    chest_open.push_back(chest4_open);

    return chest_open;
    chest_open.clear();

}

void Map_Texture::is_this_fresh_file(bool it_is, std::vector<bool> chest)
{
    if(it_is)
    {
       fresh_file=1;
       chest1_open=chest[0];
       chest2_open=chest[1];
       chest3_open=chest[2];
       chest4_open=chest[3];
    }
    else
    {


        fresh_file=0;
        chest1_open=chest[0];
        chest2_open=chest[1];
        chest3_open=chest[2];
        chest4_open=chest[3];

    }
}

void Map_Texture::reset()
{
  Tutorial_part=1;

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


    sf::RectangleShape Platform (sf::Vector2f(grid_size,grid_size));
    int elements_pushed=0;
    map.open("map.txt");
    int linia ;
    std::vector <int> platforms;

    while(map>>linia)
    {
       platforms.push_back(linia) ;
    }

    for(int i=0; i<platforms.size(); i+=32)
    {

        for(int x=0; x<32; x++)
        {
            if(platforms[i+x]==1)
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
    target.draw(BackGround_T, states);
}

BackGround::BackGround()
{
    BackGround_Texture.loadFromFile("Wall2.png");
    BackGround_Texture.setRepeated(true);
    BackGround_T.setTexture(BackGround_Texture);
    BackGround_T.setTextureRect(sf::IntRect(0, 0, 1920, 2080));
    BackGround_T.setPosition(0,-1000);
}

