#include <iostream>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <Player.h>
#include <Map.h>

void Saving(std::fstream &Save , sf::Vector2f position, std::vector<bool> chests) //Saving function
{
    Save<<position.x+2<<std::endl;
    Save<<position.y+2<<std::endl;
    Save<<chests[0]<<std::endl;
    Save<<chests[1]<<std::endl;
    Save<<chests[2]<<std::endl;
    Save<<chests[3]<<std::endl;
    Save<<chests[4]<<std::endl;
}

int main()
{

    int number_of_saves = 0;
    int screen_width=1920;
    int screen_height=1080;
    std::vector<bool> if_file_exist;

    sf::Vector2f Spawn;
    int Current_Save=0;

    std::fstream Save1;
    Save1.open( "Save1" );
    std::fstream Save2;
    Save2.open( "Save2");
    std::fstream Save3;
    Save3.open( "Save3");

    Save1.close();
    Save2.close();
    Save3.close();




    if(Save1)
    {
        if_file_exist.push_back(1);
        number_of_saves++;
    }
    else
    {
      if_file_exist.push_back(0);
    }
    if(Save2)
    {
        if_file_exist.push_back(1);
        number_of_saves++;
    }
    else
    {
      if_file_exist.push_back(0);
    }
    if(Save3)
    {
        if_file_exist.push_back(1);
        number_of_saves++;
    }
    else
    {
      if_file_exist.push_back(0);
    }

    //    Window_value Setup
    //    value 1 - main menu
    //    value 2 - Load menu
    //    value 3 - setting menu
    //    value 4 - Graphics menu
    //    value 5 - Resize menu
    //    value 6 - actual game
    //    value 7 - Pause menu
    //    value 8 - file choose menu
    //    value 9 - Audio menu
    //    value 10 - secret room




//###############################################################################################################
    int window_value=1;

    float Time = 0;


    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Sky Is The Limit");
    sf::View view(sf::Vector2f(960,540), sf::Vector2f(screen_width, screen_height));
    window.setFramerateLimit(120);
    sf::Clock deltaClock;


    // Declare a new music
    sf::Music music;

    // Open it from an audio file
    if (!music.openFromFile("Ambience.ogg"))
    {
        // error...
    }
    music.setPitch(0.5);           // increase the pitch
    music.setVolume(35);         // reduce the volume
    music.setLoop(true);         // make it loop
    bool ambient_playing=0;




    //Buttons position
    sf::Vector2f Top (200.0, 200.0);
    sf::Vector2f Middle (200.0, 500.0);
    sf::Vector2f Bottom (200.0, 800.0);
    sf::Vector2f Top_moved (Top.x+10,Top.y);
    sf::Vector2f Middle_moved (Middle.x+10,Middle.y);
    sf::Vector2f Bottom_moved (Bottom.x+10,Bottom.y);
    sf::Vector2f Common_scale (2,2);

//#####################################################################################
//Main menu Icons

    sf::Texture Background_Texture;
    sf::Texture Start_Texture;
    sf::Texture Settings_Texture;
    sf::Texture Exit_Game_Texture;

    sf::Sprite Background;

    Background_Texture.loadFromFile("screen.jpg");
    Background.setTexture(Background_Texture);
    Background.setScale(1,1);

    sf::Sprite Start;
    Start.setPosition (Top);
    Start_Texture.loadFromFile("Start 192x48.png");
    Start.setTexture(Start_Texture);
    Start.setScale(Common_scale);

    sf::Sprite Settings;
    Settings.setPosition(Middle);
    Settings_Texture.loadFromFile("Settings 192x48.png");
    Settings.setTexture(Settings_Texture);
    Settings.setScale(Common_scale);

    sf::Sprite Exit_Game;
    Exit_Game.setPosition(Bottom);
    Exit_Game_Texture.loadFromFile("Quit Game 192x48.png");
    Exit_Game.setTexture(Exit_Game_Texture);
    Exit_Game.setScale(Common_scale);


//#####################################################################################
//Saving Icons

    sf::Texture Load_Texture;
    sf::Texture New_Game_Texture;
    sf::Texture Continue_Game_Texture;
    sf::Texture Empty_Texture;
    sf::Texture Save1_Texture;
    sf::Texture Save2_Texture;
    sf::Texture Save3_Texture;

    sf::Sprite Load;
    Load.setPosition(Middle);
    Load_Texture.loadFromFile("Load 192x48.png");
    Load.setTexture(Load_Texture);
    Load.setScale(Common_scale);

    sf::Sprite New_Game;
    New_Game.setPosition(Top);
    New_Game_Texture.loadFromFile("New Game 192x48.png");
    New_Game.setTexture(New_Game_Texture);
    New_Game.setScale(Common_scale);

    sf::Sprite Continue_Game;
    Continue_Game.setPosition(Top);
    Continue_Game_Texture.loadFromFile("Continue Game 192x48.png");
    Continue_Game.setTexture(Continue_Game_Texture);
    Continue_Game.setScale(Common_scale);

    sf::Sprite Empty1;
    sf::Sprite Empty2;
    sf::Sprite Empty3;
    Empty1.setPosition(Top);
    Empty2.setPosition(sf::Vector2f(200.f,400));
    Empty3.setPosition(sf::Vector2f(200.f,600));
    Empty_Texture.loadFromFile("Empty.png");
    Empty1.setTexture(Empty_Texture);
    Empty2.setTexture(Empty_Texture);
    Empty3.setTexture(Empty_Texture);
    Empty1.setScale(Common_scale);
    Empty2.setScale(Common_scale);
    Empty3.setScale(Common_scale);

    sf::Sprite Save_1;
    Save_1.setPosition(Top);
    Save1_Texture.loadFromFile("Save_1.png");
    Save_1.setTexture(Save1_Texture);
    Save_1.setScale(Common_scale);

    sf::Sprite Save_2;
    Save_2.setPosition(sf::Vector2f(200.f,400));
    Save2_Texture.loadFromFile("Save_2.png");
    Save_2.setTexture(Save2_Texture);
    Save_2.setScale(Common_scale);

    sf::Sprite Save_3;
    Save_3.setPosition(sf::Vector2f(200.f,600));
    Save3_Texture.loadFromFile("Save_3.png");
    Save_3.setTexture(Save3_Texture);
    Save_3.setScale(Common_scale);




//#####################################################################################
//Settings menu Icons

    sf::Texture Audio_Texture;
    sf::Texture Graphics_Texture;
    sf::Texture Exit_Texture;

    sf::Sprite Audio;
    Audio.setPosition(Top);
    Audio_Texture.loadFromFile("Audio 192x48.png");
    Audio.setTexture(Audio_Texture);
    Audio.setScale(Common_scale);

    sf::Sprite Graphics;
    Graphics.setPosition(Middle);
    Graphics_Texture.loadFromFile("Graphics 192x48.png");
    Graphics.setTexture(Graphics_Texture);
    Graphics.setScale(Common_scale);

    sf::Sprite Exit;
    Exit.setPosition(Bottom);
    Exit_Texture.loadFromFile("Exit 192x48.png");
    Exit.setTexture(Exit_Texture);
    Exit.setScale(Common_scale);

//#####################################################################################
//Graphics Menu Icons

    sf::Texture Window_Resize_Texture;
    sf::Texture Toggle_Texture;
    sf::Texture RTX_Texture;

    sf::Sprite Window_Resize;
    Window_Resize.setPosition(Top);
    Window_Resize_Texture.loadFromFile("Window Resize.png");
    Window_Resize.setTexture(Window_Resize_Texture);
    Window_Resize.setScale(Common_scale);

    sf::Sprite Toggle1;
    Toggle1.setPosition(Middle);
    Toggle_Texture.loadFromFile("img_522367.png");
    Toggle1.setTexture(Toggle_Texture);
    Toggle1.setScale(0.2,0.2);

    sf::Sprite Toggle2;
    Toggle2.setPosition(Middle);
    RTX_Texture.loadFromFile("rtx.png");
    Toggle2.setTexture(RTX_Texture);
    Toggle2.setScale(Common_scale);

    std::vector<sf::IntRect> Toggle_Position;

    Toggle_Position.push_back(sf::IntRect(0, 0, 978, 455));
    Toggle_Position.push_back(sf::IntRect(0, 540, 978, 455));
    Toggle_Position.push_back(sf::IntRect(0, 119, 110, 48));
    Toggle_Position.push_back(sf::IntRect(0, 311, 110, 48));
    bool Toggle1_option=1;
    bool Toggle2_option=1;
    bool Mouse_pressed=0;


    sf::Font font_;
    sf::Text RTX_Text;
    font_.loadFromFile("OpenSans-Bold.ttf");
    RTX_Text.setFont(font_);
    RTX_Text.setCharacterSize(69);
    RTX_Text.setPosition(500.f,Middle.y);
    RTX_Text.setString("Does absolutly nothing");

    sf::Text Audio_Text;
    font_.loadFromFile("OpenSans-Bold.ttf");
    Audio_Text.setFont(font_);
    Audio_Text.setCharacterSize(69);
    Audio_Text.setPosition(Top);
    Audio_Text.setString("Turn ON/OFF ambient sounds of the game");

//#####################################################################################
//Resize Menu Icons

    sf::Texture r720t;
    sf::Texture r1280t;
    sf::Texture r1920t;
    sf::Texture r2560t;

    sf::Sprite r720;
    r720.setPosition(Top);
    r720t.loadFromFile("720.png");
    r720.setTexture(r720t);
    r720.setScale(Common_scale);

    sf::Sprite r1280;
    r1280.setPosition(Middle);
    r1280t.loadFromFile("1280.png");
    r1280.setTexture(r1280t);
    r1280.setScale(Common_scale);

    sf::Sprite r1920;
    r1920.setPosition(850.0, 200.0);
    r1920t.loadFromFile("1920.png");
    r1920.setTexture(r1920t);
    r1920.setScale(Common_scale);

    sf::Sprite r2560;
    r2560.setPosition(850.0, 500.0);
    r2560t.loadFromFile("2560.png");
    r2560.setTexture(r2560t);
    r2560.setScale(Common_scale);


//#####################################################################################
//Pause Menu Icons

    sf::Texture Back_Texture;
    sf::Texture Resume_Texture;


    sf::Sprite Back;
    Back.setPosition(Bottom);
    Back_Texture.loadFromFile("Back.png");
    Back.setTexture(Back_Texture);
    Back.setScale(Common_scale);

    sf::Sprite Resume;
    Resume.setPosition(Top);
    Resume_Texture.loadFromFile("Resume.png");
    Resume.setTexture(Resume_Texture);
    Resume.setScale(Common_scale);

//#####################################################################################
//Class Declaration

    Player p1;
    Level_Platforms p2;
    Player_Animation p3;
    Player_Texture p4;
    BackGround p5;
    Player_Sounds p6;
    Map_Texture p7;
    Glados p8;

//#####################################################################################


    bool pause_menu=0;
    const float MaxDelta=0.1;
//#####################################################################################
//Game Loop

    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();         
            window.setSize(sf::Vector2u(screen_width, screen_height));

        }

        sf::Time Delta = deltaClock.restart();

        float Second = Delta.asSeconds();
        if(Second>MaxDelta)
            Second=MaxDelta;


if(window_value==6)
{
         view.setCenter(960,p1.camera_position(window_value, view.getCenter().y));
}
else
{
    view.setCenter(960,540);
}
window.setView(view);


        //#####################################################################################
        sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));


        if(!(sf::Mouse::isButtonPressed(sf::Mouse::Left)))
        {

            Mouse_pressed=0;
        }

        //#####################################################################################
        //Start Button
        if(mouse_pos.x>= Start.getGlobalBounds().left &&
                mouse_pos.x<= Start.getGlobalBounds().left+Start.getGlobalBounds().width &&
                mouse_pos.y>= Start.getGlobalBounds().top &&
                mouse_pos.y<= Start.getGlobalBounds().top+Start.getGlobalBounds().height
                && window_value==1)
        {
            Start.setPosition(Top_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=2;
                }
            }

        }
        else
        {
           Start.setPosition(Top);
        }


        //#####################################################################################
        //New_Game Button
        if(mouse_pos.x>= New_Game.getGlobalBounds().left &&
                mouse_pos.x<= New_Game.getGlobalBounds().left+Start.getGlobalBounds().width &&
                mouse_pos.y>= New_Game.getGlobalBounds().top &&
                mouse_pos.y<= New_Game.getGlobalBounds().top+Start.getGlobalBounds().height
                && window_value==2 && number_of_saves==0)
        {
            New_Game.setPosition(Top_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=6;
                    Current_Save=1;
                    number_of_saves++;
                    Save1.open("Save1", std::ios::out );
                    Save1.close();
                    std::vector<bool> chest;
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    if_file_exist[0]=1;
                    p7.is_this_fresh_file(1, chest);
                    chest.clear();
                }
            }

        }
        else
        {
            New_Game.setPosition(Top);
        }

        //#####################################################################################
        //Continue_Game Button
        if(mouse_pos.x>= Continue_Game.getGlobalBounds().left &&
                mouse_pos.x<= Continue_Game.getGlobalBounds().left+Start.getGlobalBounds().width &&
                mouse_pos.y>= Continue_Game.getGlobalBounds().top &&
                mouse_pos.y<= Continue_Game.getGlobalBounds().top+Start.getGlobalBounds().height
                && window_value==2 && number_of_saves>0)
        {
            Continue_Game.setPosition(Top_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=6;
                    Current_Save=1;
                    std::vector<bool> chest;
                    Save1.open("Save1");
                    std::string linia ;
                    int nr_lini=1;
                    for(int i = 0; i<7; i++)
                    {
                        std::getline(Save1, linia);
                        switch (nr_lini)
                        {
                        case 1: Spawn.x = ::atof(linia.c_str()); break;
                        case 2: Spawn.y = ::atof(linia.c_str()); break;
                        case 3:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 4:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 5:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 6:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 7:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        }
                        nr_lini++;
                    }
                    Save1.close();
                    p1.getPosition(number_of_saves, Spawn);
                    p7.is_this_fresh_file(0, chest);
                    p6.file_exist(chest);
                    chest.clear();
                }
            }
        }
        else
        {
            Continue_Game.setPosition(Top);
        }
        //#####################################################################################
        //Load Button
        if(mouse_pos.x>= Load.getGlobalBounds().left &&
                mouse_pos.x<= Load.getGlobalBounds().left+Start.getGlobalBounds().width &&
                mouse_pos.y>= Load.getGlobalBounds().top &&
                mouse_pos.y<= Load.getGlobalBounds().top+Start.getGlobalBounds().height
                && window_value==2)
        {
            Load.setPosition(Middle_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=8;
                }
            }
        }
        else
        {
            Load.setPosition(Middle);
        }

        //#####################################################################################
        //Empty1 Button
        if(mouse_pos.x>= Empty1.getGlobalBounds().left &&
                mouse_pos.x<= Empty1.getGlobalBounds().left+Start.getGlobalBounds().width &&
                mouse_pos.y>= Empty1.getGlobalBounds().top &&
                mouse_pos.y<= Empty1.getGlobalBounds().top+Start.getGlobalBounds().height
                && window_value==8 && if_file_exist[0]==0)
        {
            Empty1.setPosition(Top_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=6;
                    Current_Save=1;
                    number_of_saves++;
                    Save1.open("Save1", std::ios::out );
                    Save1.close();
                    std::vector<bool> chest;
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    if_file_exist[0]=1;
                    p1.getPosition(number_of_saves, sf::Vector2f(1200.f,900.f));
                    p7.is_this_fresh_file(1, chest);
                    chest.clear();
                }
            }
        }
        else
        {
            Empty1.setPosition(Top);
        }

        //#####################################################################################
        //Empty2 Button
        if(mouse_pos.x>= Empty2.getGlobalBounds().left &&
                mouse_pos.x<= Empty2.getGlobalBounds().left+Start.getGlobalBounds().width &&
                mouse_pos.y>= Empty2.getGlobalBounds().top &&
                mouse_pos.y<= Empty2.getGlobalBounds().top+Start.getGlobalBounds().height
                && window_value==8 && if_file_exist[1]==0)
        {
            Empty2.setPosition(sf::Vector2f(210.f,400));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=6;
                    Current_Save=2;
                    number_of_saves++;
                    Save2.open("Save2", std::ios::out );
                    Save2.close();
                    std::vector<bool> chest;
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    if_file_exist[1]=1;
                    p1.getPosition(number_of_saves, sf::Vector2f(1200.f,900.f));
                    p7.is_this_fresh_file(1, chest);
                    chest.clear();
                }
            }
        }
        else
        {
            Empty2.setPosition(sf::Vector2f(200.f,400));
        }

        //#####################################################################################
        //Empty3 Button
        if(mouse_pos.x>= Empty3.getGlobalBounds().left &&
                mouse_pos.x<= Empty3.getGlobalBounds().left+Start.getGlobalBounds().width &&
                mouse_pos.y>= Empty3.getGlobalBounds().top &&
                mouse_pos.y<= Empty3.getGlobalBounds().top+Start.getGlobalBounds().height
                && window_value==8 && if_file_exist[2]==0)
        {
            Empty3.setPosition(sf::Vector2f(210.f,600));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    Current_Save=3;
                    window_value=6;
                    number_of_saves++;
                    Save3.open("Save3", std::ios::out );
                    Save3.close();
                    std::vector<bool> chest;
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    chest.push_back(0);
                    if_file_exist[2]=1;
                    p1.getPosition(number_of_saves, sf::Vector2f(1200.f,900.f));
                    p7.is_this_fresh_file(1, chest);
                    chest.clear();
                }
            }
        }
        else
        {
            Empty3.setPosition(sf::Vector2f(200.f,600));
        }

        //#####################################################################################
        //Save_1 Button
        if(mouse_pos.x>= Save_1.getGlobalBounds().left &&
                mouse_pos.x<= Save_1.getGlobalBounds().left+Start.getGlobalBounds().width &&
                mouse_pos.y>= Save_1.getGlobalBounds().top &&
                mouse_pos.y<= Save_1.getGlobalBounds().top+Start.getGlobalBounds().height
                && window_value==8 && if_file_exist[0]==1)
        {
            Save_1.setPosition(Top_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=6;
                    Current_Save=1;
                    std::vector<bool> chest;
                    Save1.open("Save1", std::ios::in);
                    std::string linia ;
                    int nr_lini=1;
                    for(int i = 0; i<7; i++)
                    {
                        std::getline(Save1, linia);
                        switch (nr_lini)
                        {
                        case 1: Spawn.x = ::atof(linia.c_str()); break;
                        case 2: Spawn.y = ::atof(linia.c_str()); break;
                        case 3:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 4:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 5:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 6:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 7:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        }
                        nr_lini++;
                    }
                    p7.is_this_fresh_file(0, chest);
                    p1.getPosition(number_of_saves, Spawn);
                    p6.file_exist(chest);
                    Save1.close();
                    chest.clear();






                }
            }
        }
        else
        {
            Save_1.setPosition(Top);
        }

        //#####################################################################################
        //Save_2 Button
        if(mouse_pos.x>= Save_2.getGlobalBounds().left &&
                mouse_pos.x<= Save_2.getGlobalBounds().left+Start.getGlobalBounds().width &&
                mouse_pos.y>= Save_2.getGlobalBounds().top &&
                mouse_pos.y<= Save_2.getGlobalBounds().top+Start.getGlobalBounds().height
                && window_value==8 && if_file_exist[1]==1)
        {
            Save_2.setPosition(sf::Vector2f(210.f,400));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=6;
                    Current_Save=2;
                    std::vector<bool> chest;
                    Save2.open("Save2", std::ios::in);
                    std::string linia ;
                    int nr_lini=1;
                    for(int i = 0; i<7; i++)
                    {
                        std::getline(Save2, linia);
                        switch (nr_lini)
                        {
                        case 1: Spawn.x = ::atof(linia.c_str()); break;
                        case 2: Spawn.y = ::atof(linia.c_str()); break;
                        case 3:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 4:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 5:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 6:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 7:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        }
                        nr_lini++;
                    }
                    p7.is_this_fresh_file(0, chest);
                    p1.getPosition(number_of_saves, Spawn);
                    p6.file_exist(chest);
                    Save2.close();

                    chest.clear();




                }
            }
        }
        else
        {
            Save_2.setPosition(sf::Vector2f(200.f,400));
        }

        //#####################################################################################
        //Save_3 Button
        if(mouse_pos.x>= Save_3.getGlobalBounds().left &&
                mouse_pos.x<= Save_3.getGlobalBounds().left+Start.getGlobalBounds().width &&
                mouse_pos.y>= Save_3.getGlobalBounds().top &&
                mouse_pos.y<= Save_3.getGlobalBounds().top+Start.getGlobalBounds().height
                && window_value==8 && if_file_exist[2]==1)
        {
            Save_3.setPosition(sf::Vector2f(210.f,600));

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    Current_Save=3;
                    window_value=6;
                    std::vector<bool> chest;

                    Save3.open("Save3", std::ios::in);
                    std::string linia ;
                    int nr_lini=1;
                    for(int i = 0; i<7; i++)
                    {
                        std::getline(Save3, linia);
                        switch (nr_lini)
                        {
                        case 1: Spawn.x = ::atof(linia.c_str()); break;
                        case 2: Spawn.y = ::atof(linia.c_str()); break;
                        case 3:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 4:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 5:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 6:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        case 7:
                            if(linia == "1"){
                                chest.push_back(true);
                            }
                            else{
                                chest.push_back(false);
                            }
                            break;
                        }
                        nr_lini++;
                    }
                    p7.is_this_fresh_file(0, chest);
                    p1.getPosition(number_of_saves, Spawn);
                    p6.file_exist(chest);
                    Save3.close();
                    chest.clear();
                }
            }
        }
        else
        {
            Save_3.setPosition(sf::Vector2f(200.f,600));
        }

        //#####################################################################################
        //Settings Button
        if(mouse_pos.x>= Settings.getGlobalBounds().left &&
                mouse_pos.x<= Settings.getGlobalBounds().left+Settings.getGlobalBounds().width &&
                mouse_pos.y>= Settings.getGlobalBounds().top &&
                mouse_pos.y<= Settings.getGlobalBounds().top+Settings.getGlobalBounds().height
                && (window_value==1 || window_value==7) )
        {
            Settings.setPosition(Middle_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=3;
                }
            }
        }
        else
        {
            Settings.setPosition(Middle);
        }

        //#####################################################################################
        //Exit_Game Button
        if(mouse_pos.x>= Exit_Game.getGlobalBounds().left &&
                mouse_pos.x<= Exit_Game.getGlobalBounds().left+Exit_Game.getGlobalBounds().width &&
                mouse_pos.y>= Exit_Game.getGlobalBounds().top &&
                mouse_pos.y<= Exit_Game.getGlobalBounds().top+Exit_Game.getGlobalBounds().height
                && window_value==1)
        {
            Exit_Game.setPosition(Bottom_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    return 0;
                }
            }
        }
        else
        {
            Exit_Game.setPosition(Bottom);
        }

        //#####################################################################################
        //Graphics Button
        if(mouse_pos.x>= Graphics.getGlobalBounds().left &&
                mouse_pos.x<= Graphics.getGlobalBounds().left+Graphics.getGlobalBounds().width &&
                mouse_pos.y>= Graphics.getGlobalBounds().top &&
                mouse_pos.y<= Graphics.getGlobalBounds().top+Graphics.getGlobalBounds().height
                && window_value==3)
        {
            Graphics.setPosition(Middle_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=4;
                }
            }
        }
        else
        {
            Graphics.setPosition(Middle);
        }

        //#####################################################################################
        //Audio Toggle
        if(mouse_pos.x>= Toggle1.getGlobalBounds().left &&
                mouse_pos.x<= Toggle1.getGlobalBounds().left+Toggle1.getGlobalBounds().width &&
                mouse_pos.y>= Toggle1.getGlobalBounds().top &&
                mouse_pos.y<= Toggle1.getGlobalBounds().top+Toggle1.getGlobalBounds().height
                && window_value==9)
        {

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    if(Toggle1_option)
                    {
                        Toggle1_option=0;
                        Mouse_pressed=1;
                    }
                }
                if(!Mouse_pressed)
                {
                    if (!Toggle1_option)
                    {
                        Toggle1_option=1;
                        Mouse_pressed=1;
                    }
                }
            }
        }



        //#####################################################################################
        //RTX Toggle
        if(mouse_pos.x>= Toggle2.getGlobalBounds().left &&
                mouse_pos.x<= Toggle2.getGlobalBounds().left+Toggle2.getGlobalBounds().width &&
                mouse_pos.y>= Toggle2.getGlobalBounds().top &&
                mouse_pos.y<= Toggle2.getGlobalBounds().top+Toggle2.getGlobalBounds().height
                && window_value==4)
        {

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    if(Toggle2_option)
                    {
                        Toggle2_option=0;
                        Mouse_pressed=1;
                    }
                }
                if(!Mouse_pressed)
                {
                    if (!Toggle2_option)
                    {
                        Toggle2_option=1;
                        Mouse_pressed=1;
                    }
                }

            }
        }

        //#####################################################################################
        //Exit Button
        if(mouse_pos.x>= Exit.getGlobalBounds().left &&
                mouse_pos.x<= Exit.getGlobalBounds().left+Exit.getGlobalBounds().width &&
                mouse_pos.y>= Exit.getGlobalBounds().top &&
                mouse_pos.y<= Exit.getGlobalBounds().top+Exit.getGlobalBounds().height
                && (window_value==2  || window_value ==7 ))
        {
            Exit.setPosition(Bottom_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    if(window_value==7)
                    {
                        if(Current_Save==1)
                        {
                            Save1.open("Save1", std::ios::out);
                            Saving(Save1, p1.Position(), p7.is_chest_open());
                            Save1.close();
                            p7.reset();
                            p6.reset();
                        }
                        if(Current_Save==2)
                        {
                            Save2.open("Save2", std::ios::out);
                            Saving(Save2, p1.Position(), p7.is_chest_open());
                            Save2.close();
                            p7.reset();
                            p6.reset();
                        }
                        if(Current_Save==3)
                        {
                            Save3.open("Save3", std::ios::out);
                            Saving(Save3, p1.Position(), p7.is_chest_open());
                            Save3.close();
                            p7.reset();
                            p6.reset();

                        }
                    }
                    window_value=1;
                    Mouse_pressed=1;
                }
            }
        }
        else
        {
            Exit.setPosition(Bottom);
        }

        //#####################################################################################
        //Window_Resize Button
        if(mouse_pos.x>= Window_Resize.getGlobalBounds().left &&
                mouse_pos.x<= Window_Resize.getGlobalBounds().left+Window_Resize.getGlobalBounds().width &&
                mouse_pos.y>= Window_Resize.getGlobalBounds().top &&
                mouse_pos.y<= Window_Resize.getGlobalBounds().top+Window_Resize.getGlobalBounds().height
                && window_value==4)
        {
            Window_Resize.setPosition(Top_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=5;
                }
            }
        }
        else
        {
            Window_Resize.setPosition(Top);
        }

        //#####################################################################################
        //Resize to 720 Button
        if(mouse_pos.x>= r720.getGlobalBounds().left &&
                mouse_pos.x<= r720.getGlobalBounds().left+r720.getGlobalBounds().width &&
                mouse_pos.y>= r720.getGlobalBounds().top &&
                mouse_pos.y<= r720.getGlobalBounds().top+r720.getGlobalBounds().height
                && window_value==5)
        {
            r720.setPosition(Top_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=4;
                    screen_width = 720;
                    screen_height = 405;
                }
            }
        }
        else
        {
            r720.setPosition(Top);
        }

        //#####################################################################################
        //Resize to 1280 Button
        if(mouse_pos.x>= r1280.getGlobalBounds().left &&
                mouse_pos.x<= r1280.getGlobalBounds().left+r1280.getGlobalBounds().width &&
                mouse_pos.y>= r1280.getGlobalBounds().top &&
                mouse_pos.y<= r1280.getGlobalBounds().top+r1280.getGlobalBounds().height
                && window_value==5)
        {
            r1280.setPosition(Middle_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=4;
                    screen_width = 1280;
                    screen_height = 720;
                }
            }
        }
        else
        {
            r1280.setPosition(Middle);
        }

        //#####################################################################################
        //Resize to 1920 Button
        if(mouse_pos.x>= r1920.getGlobalBounds().left &&
                mouse_pos.x<= r1920.getGlobalBounds().left+r1920.getGlobalBounds().width &&
                mouse_pos.y>= r1920.getGlobalBounds().top &&
                mouse_pos.y<= r1920.getGlobalBounds().top+r1920.getGlobalBounds().height
                && window_value==5)
        {
            r1920.setPosition(860.0, 200.0);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=4;
                    screen_width = 1920;
                    screen_height = 1080;
                }
            }
        }
        else
        {
            r1920.setPosition(850.0, 200.0);
        }

        //#####################################################################################
        //Resize to 2560 Button
        if(mouse_pos.x>= r2560 .getGlobalBounds().left &&
                mouse_pos.x<= r2560.getGlobalBounds().left+r2560.getGlobalBounds().width &&
                mouse_pos.y>= r2560.getGlobalBounds().top &&
                mouse_pos.y<= r2560.getGlobalBounds().top+r2560.getGlobalBounds().height
                && window_value==5 )
        {
            r2560.setPosition(860.0, 500.0);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=4;
                    screen_width = 2560;
                    screen_height = 1440;
                }
            }
        }
        else
        {
            r2560.setPosition(850.0, 500.0);
        }


        //#####################################################################################
        //Resume Button
        if(mouse_pos.x>= Resume .getGlobalBounds().left &&
                mouse_pos.x<= Resume.getGlobalBounds().left+Resume.getGlobalBounds().width &&
                mouse_pos.y>= Resume.getGlobalBounds().top &&
                mouse_pos.y<= Resume.getGlobalBounds().top+Resume.getGlobalBounds().height
                && window_value==7 )
        {
            Resume.setPosition(Top_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    Mouse_pressed=1;
                    window_value=6;
                }
            }
        }
        else
        {
            Resume.setPosition(Top);
        }

        //#####################################################################################
        //Back Button
        if(mouse_pos.x>= Back .getGlobalBounds().left &&
                mouse_pos.x<= Back.getGlobalBounds().left+Back.getGlobalBounds().width &&
                mouse_pos.y>= Back.getGlobalBounds().top &&
                mouse_pos.y<= Back.getGlobalBounds().top+Back.getGlobalBounds().height
                && (window_value==7 || window_value==2  || window_value==3 || window_value==4
                    || window_value==5  || window_value==8 || window_value==9))
        {
            Back.setPosition(Bottom_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {

                if(!Mouse_pressed)
                {
                    if(window_value==2)
                    {
                        window_value=1;
                    }
                    if(window_value==3)
                    {
                        if(pause_menu)
                        {
                            window_value=7;
                        }
                        else
                            window_value=1;
                    }
                    if(window_value==4)
                    {
                        window_value=3;
                    }
                    if(window_value==5)
                    {
                        window_value=4;
                    }
                    if(window_value==8)
                    {
                        window_value=2;
                    }
                    if(window_value==9)
                    {
                        window_value=3;
                    }



                    Mouse_pressed=1;

                }
            }
        }
        else
        {
            Back.setPosition(Bottom);
        }

        //#####################################################################################
        //Audio Button
        if(mouse_pos.x>= Audio .getGlobalBounds().left &&
                mouse_pos.x<= Audio.getGlobalBounds().left+Audio.getGlobalBounds().width &&
                mouse_pos.y>= Audio.getGlobalBounds().top &&
                mouse_pos.y<= Audio.getGlobalBounds().top+Audio.getGlobalBounds().height
                && window_value==3)
        {
            Audio.setPosition(Top_moved);

            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(!Mouse_pressed)
                {
                    window_value=9;
                    Mouse_pressed=1;

                }
            }
        }
        else
        {
            Audio.setPosition(Top);
        }

        //#####################################################################################


    if(window_value==6)
    {

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            window_value=7;
            pause_menu=1;
        }

    }

        if(Toggle1_option)
            Toggle1.setTextureRect(Toggle_Position[0]);
        else
            Toggle1.setTextureRect(Toggle_Position[1]);

        if(Toggle2_option)
            Toggle2.setTextureRect(Toggle_Position[2]);
        else
            Toggle2.setTextureRect(Toggle_Position[3]);


//#####################################################################################

        Time+=Time+Second;
        p6.Sound_movement(window_value, p7.is_chest_open());
        p1.Movement(Second, window_value,p7.is_chest_open());

        p1.Collisions(window_value);
        p4.Movement_T(p1.Position(), Second); // player tracking for texture
        p7.Chest_state(p1.Player_bounds());
        p7.Map_animation(Second, p1.camera_position(window_value, view.getCenter().y));
        p3.dash_bar_animation(view.getCenter().y, Second);
        p7.Cheat_window(mouse_pos);


        if(p7.Dor(p1.Player_bounds())==10)
        {
            window_value=10;
        }

//#####################################################################################



        window.clear(sf::Color::Black);

        if(window_value==1)             //menu screen
        {
            window.draw(Background);
            window.draw(Start);
            window.draw(Settings);
            window.draw(Exit_Game);
        }
        else if (window_value==2)       //Load menu
        {
            window.draw(Background);
            if(number_of_saves==0)
            {
                window.draw(New_Game);
            }

            if(number_of_saves>0)
            {
                window.draw(Continue_Game);
            }

            window.draw(Load);
            window.draw(Back);
        }
        else if (window_value==3)       //Settings menu
        {
            window.draw(Background);
            window.draw(Audio);
            window.draw(Graphics);
            window.draw(Back);
        }
        else if (window_value==4)       //Graphics menu
        {
            window.draw(Background);
            window.draw(Window_Resize);

            window.draw(Toggle2);
            if(!Toggle2_option)
            {
                window.draw(RTX_Text);
            }
            window.draw(Back);

        }
        else if (window_value==5)       //Resize menu
        {
            window.draw(Background);
            window.draw(r720);
            window.draw(r1280);
            window.draw(r1920);
            window.draw(r2560);
            window.draw(Back);
        }
        else if(window_value==6)        //actual game
        {
            if(ambient_playing==0 && Toggle1_option)
            {
                music.play();
                ambient_playing=1;
            }
            window.draw(p1);
            window.draw(p5);
            window.draw(p2);


            window.draw(p3);
            window.draw(p7);
            window.draw(p4);



        }
        else if (window_value==7)       //Pause menu
        {

           window.draw(Background);
           window.draw(Resume);
           window.draw(Settings);
           window.draw(Exit);

        }
        else if (window_value==8)       //file choose menu
        {

            window.draw(Background);

            if(if_file_exist[0])
                window.draw(Save_1);
            else
                window.draw(Empty1);

            if(if_file_exist[1])
                window.draw(Save_2);

            else
                window.draw(Empty2);

            if(if_file_exist[2])
                window.draw(Save_3);

            else
                window.draw(Empty3);

            window.draw(Back);
        }
        else if (window_value==9)       //Audio menu
        {
            window.draw(Background);
            window.draw(Audio_Text);
            window.draw(Toggle1);


            window.draw(Back);
        }
        else if (window_value==10)      //Glados ester egg
        {
            p8.Timer(Second);
            p8.Glados_animation(Second);
            window.draw(p8);
            if(p8.End()>8.f)
            {
                if(Current_Save==1)
                {
                    Save1.open("Save1", std::ios::out);
                    Saving(Save1, p1.Position(), p7.is_chest_open());
                    Save1.close();

                }
                if(Current_Save==2)
                {
                    Save2.open("Save2", std::ios::out);
                    Saving(Save2, p1.Position(), p7.is_chest_open());
                    Save2.close();

                }
                if(Current_Save==3)
                {
                    Save3.open("Save3", std::ios::out);
                    Saving(Save3, p1.Position(), p7.is_chest_open());
                    Save3.close();


                }
                return 0;
            }

        }

        if (window_value!=6)
        {
           ambient_playing=0;
          music.pause();
        }

        window.display();
    }





    return 0;
}
