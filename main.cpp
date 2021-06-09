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

int main()
{
       // to future dipshit
    // jeśli wyjebiesz zapis rozmiaru okna twoje problemy znikną
    // wybierz zapis domyślny 1920x1080 i reszte zapisów zostaw jako
    // boole, zmienne i pozycje przeskalowaną do oryginalnego rozmiaru
    // wszystko się skaluje jak zmieniasz rozmiar okna w trakcie sesji
    int number_of_saves = 0;
    int screen_width;
    int screen_height;
    double scale_factor;

    std::fstream Save1;
    Save1.open( "Save1" );
    std::fstream Save2;
    Save2.open( "Save2");
    std::fstream Save3;
    Save3.open( "Save3");

    if(Save1)
    {
        std::cout<<"file exists";
    }
    else
    {
        std:: cout<<"file doesn't exist";
        Save1.open("Save1", std::ios::out );
        number_of_saves=1;
        Save1<<1920<<std::endl; //screen width
        Save1<<1080<<std::endl; //screen hight
        Save1<<1<<std::endl;    //scale factor


    }
    Save1.close();

    Save1.open("Save1");


    std::string linia ;
    int nr_lini=1;
    for(int i = 0; i<3; i++)
    {
        std::getline(Save1, linia);
        switch (nr_lini)
        {
        case 1: screen_width = atoi(linia.c_str()); break;
        case 2: screen_height = atoi(linia.c_str()); break;
        case 3: scale_factor =atof (linia.c_str()); break;
        }
        nr_lini++;
    }
    Save1.close();
    std::cout<<screen_width<<std::endl;
    std::cout<<screen_height<<std::endl;
    std::cout<<scale_factor<<std::endl;



    int window_value=6;
    int first_save=1;       //will be read from only Save1
    float Time = 0;


    sf::RenderWindow window(sf::VideoMode(screen_width, screen_height), "Sky Is The Limit");

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


//    Window_value Setup
//    value 1 - main menu
//    value 2 - saves menu
//    value 3 - setting menu
//    value 4 - resize menu
//    value 5 - pause menu
//    value 6 - actual game
//    value 1
//    value 1


    sf::Vector2f Top (scale_factor*200.0, scale_factor*200.0);
    sf::Vector2f Middle (scale_factor*200.0, scale_factor*500.0);
    sf::Vector2f Bottom (scale_factor*200.0, scale_factor*800.0);
    sf::Vector2f Common_scale (scale_factor*2,scale_factor*2);

//#####################################################################################
//Main menu

    sf::Texture Background_Texture;
    sf::Texture Start_Texture;
    sf::Texture Settings_Texture;
    sf::Texture Exit_Game_Texture;

    sf::Sprite Background;

    Background_Texture.loadFromFile("screen.jpg");
    Background.setTexture(Background_Texture);
    Background.setScale(scale_factor*1,scale_factor*1);

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

    sf::Texture Load_Texture;
    sf::Texture New_Game_Texture;
    sf::Texture Continue_Game_Texture;

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
    New_Game.setPosition(Top);
    Continue_Game_Texture.loadFromFile("Continue Game 192x48.png");
    New_Game.setTexture(Continue_Game_Texture);
    New_Game.setScale(Common_scale);


//#####################################################################################
//Settings menu

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
//Graphics Menu

    sf::Texture Window_Resize_Texture;
    sf::Texture Toggle_Texture;
    sf::Texture RTX_Texture;

    sf::Sprite Window_Resize;
    Window_Resize.setPosition(Top);
    Window_Resize_Texture.loadFromFile("Window Resize.png");
    Window_Resize.setTexture(Window_Resize_Texture);
    Window_Resize.setScale(Common_scale);

    sf::Sprite Toggle1;
    Toggle1.setPosition(scale_factor*200.0,scale_factor*420.0);
    Toggle_Texture.loadFromFile("img_522367.png");
    Toggle1.setTexture(Toggle_Texture);
    Toggle1.setScale(scale_factor*0.2,scale_factor*0.2);

    sf::Sprite Toggle2;
    Toggle2.setPosition(scale_factor*200.0,scale_factor*575.0);
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

//#####################################################################################
//Resize Menu
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
    r1920.setPosition(scale_factor*850.0, scale_factor*200.0);
    r1920t.loadFromFile("1920.png");
    r1920.setTexture(r1920t);
    r1920.setScale(Common_scale);

    sf::Sprite r2560;
    r2560.setPosition(scale_factor*850.0, scale_factor*500.0);
    r2560t.loadFromFile("2560.png");
    r2560.setTexture(r2560t);
    r2560.setScale(Common_scale);

//#####################################################################################
    Player p1;
    Level_Platforms p2;
    //Level_Walls p3;
    Player_Texture p4;
    BackGround p5;
    Player_Sounds p6;


    //p2.scale(scale_factor);
//    p1.scale(scale_factor);


    sf::SoundBuffer buffer;
    buffer.loadFromFile("SFX_Jump_09.wav");
    sf::Sound sound;
    sound.setBuffer(buffer);




    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();         
            window.setSize(sf::Vector2u(screen_width, screen_height));

        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
           // sf::Vector2i mouse_pos = sf::Mouse::getPosition(window);
        sf::Vector2f mouse_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            mouse_pos.x = mouse_pos.x;//scale_factor;
            mouse_pos.y = mouse_pos.y;//scale_factor;
            std::cout<<mouse_pos.x<<"  "<<mouse_pos.y<<std::endl;
            //Load menu
            if(mouse_pos.x>= Start.getGlobalBounds().left &&
                    mouse_pos.x<= Start.getGlobalBounds().left+Start.getGlobalBounds().width &&
                    mouse_pos.y>= Start.getGlobalBounds().top &&
                    mouse_pos.y<= Start.getGlobalBounds().top+Start.getGlobalBounds().height
                    && window_value==1)
            {
                if(!Mouse_pressed)
                {
                Mouse_pressed=1;
                window_value=2;
                }
            }
            if(mouse_pos.x>= Start.getGlobalBounds().left &&
                    mouse_pos.x<= Start.getGlobalBounds().left+Start.getGlobalBounds().width &&
                    mouse_pos.y>= Start.getGlobalBounds().top &&
                    mouse_pos.y<= Start.getGlobalBounds().top+Start.getGlobalBounds().height
                    && window_value==2 && first_save==1)
            {
                if(!Mouse_pressed)
                {
                Mouse_pressed=1;
                window_value=6;
                }
            }
            //Settings
            else if(mouse_pos.x>= Settings.getGlobalBounds().left &&
                    mouse_pos.x<= Settings.getGlobalBounds().left+Settings.getGlobalBounds().width &&
                    mouse_pos.y>= Settings.getGlobalBounds().top &&
                    mouse_pos.y<= Settings.getGlobalBounds().top+Settings.getGlobalBounds().height
                    && window_value==1)
            {
                if(!Mouse_pressed)
                {
                Mouse_pressed=1;
                window_value=3;
                }
            }
            //Exit Game
            else if(mouse_pos.x>= Exit_Game.getGlobalBounds().left &&
                    mouse_pos.x<= Exit_Game.getGlobalBounds().left+Exit_Game.getGlobalBounds().width &&
                    mouse_pos.y>= Exit_Game.getGlobalBounds().top &&
                    mouse_pos.y<= Exit_Game.getGlobalBounds().top+Exit_Game.getGlobalBounds().height
                    && window_value==1)
            {
                if(!Mouse_pressed)
                {
                    if(number_of_saves<2)
                    {
                        std::cout<<screen_width<<std::endl;
                        std::cout<<screen_height<<std::endl;
                        std::cout<<scale_factor<<std::endl;
                        Save1.open("Save1", std::ios::out);
                        Save1<<screen_width<<std::endl;
                        Save1<<screen_height<<std::endl;
                        Save1<<scale_factor<<std::endl;
                        Save1.close();
                    }
                return 0;
                }
            }

            else if(mouse_pos.x>= Graphics.getGlobalBounds().left &&
                    mouse_pos.x<= Graphics.getGlobalBounds().left+Graphics.getGlobalBounds().width &&
                    mouse_pos.y>= Graphics.getGlobalBounds().top &&
                    mouse_pos.y<= Graphics.getGlobalBounds().top+Graphics.getGlobalBounds().height
                    && window_value==3)
            {
                if(!Mouse_pressed)
                {
                Mouse_pressed=1;
                window_value=4;
                }
            }
            else if(mouse_pos.x>= Toggle1.getGlobalBounds().left &&
                    mouse_pos.x<= Toggle1.getGlobalBounds().left+Toggle1.getGlobalBounds().width &&
                    mouse_pos.y>= Toggle1.getGlobalBounds().top &&
                    mouse_pos.y<= Toggle1.getGlobalBounds().top+Toggle1.getGlobalBounds().height
                    && window_value==4)
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
            else if(mouse_pos.x>= Toggle2.getGlobalBounds().left &&
                    mouse_pos.x<= Toggle2.getGlobalBounds().left+Toggle2.getGlobalBounds().width &&
                    mouse_pos.y>= Toggle2.getGlobalBounds().top &&
                    mouse_pos.y<= Toggle2.getGlobalBounds().top+Toggle2.getGlobalBounds().height
                    && window_value==4)
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
            else if(mouse_pos.x>= Exit.getGlobalBounds().left &&
                    mouse_pos.x<= Exit.getGlobalBounds().left+Exit.getGlobalBounds().width &&
                    mouse_pos.y>= Exit.getGlobalBounds().top &&
                    mouse_pos.y<= Exit.getGlobalBounds().top+Exit.getGlobalBounds().height
                    && (window_value==2 || window_value==3 || window_value==4 || window_value==5
                    || window_value ==7))
            {
                if(!Mouse_pressed)
                {
                Mouse_pressed=1;
                window_value=1;
                }
            }
            //Resize
            else if(mouse_pos.x>= Window_Resize.getGlobalBounds().left &&
                    mouse_pos.x<= Window_Resize.getGlobalBounds().left+Window_Resize.getGlobalBounds().width &&
                    mouse_pos.y>= Window_Resize.getGlobalBounds().top &&
                    mouse_pos.y<= Window_Resize.getGlobalBounds().top+Window_Resize.getGlobalBounds().height
                    && window_value==4)
            {
                std::cout<<Window_Resize.getGlobalBounds().top<<"   "<<Window_Resize.getGlobalBounds().left<<std::endl;
                if(!Mouse_pressed)
                {
                Mouse_pressed=1;
                window_value=5;
                }
            }
            else if(mouse_pos.x>= r720.getGlobalBounds().left &&
                    mouse_pos.x<= r720.getGlobalBounds().left+r720.getGlobalBounds().width &&
                    mouse_pos.y>= r720.getGlobalBounds().top &&
                    mouse_pos.y<= r720.getGlobalBounds().top+r720.getGlobalBounds().height
                    && window_value==5)
            {
                if(!Mouse_pressed)
                {
                Mouse_pressed=1;
                window_value=4;
                screen_width = 720;
                screen_height = 405;        //do poprawki
                 scale_factor=0.375;
                }
            }
            else if(mouse_pos.x>= r1280.getGlobalBounds().left &&
                    mouse_pos.x<= r1280.getGlobalBounds().left+r1280.getGlobalBounds().width &&
                    mouse_pos.y>= r1280.getGlobalBounds().top &&
                    mouse_pos.y<= r1280.getGlobalBounds().top+r1280.getGlobalBounds().height
                    && window_value==5)
            {
                if(!Mouse_pressed)
                {
                Mouse_pressed=1;
                window_value=4;
                screen_width = 1280;
                screen_height = 720;
                scale_factor=0.66666666666666666666666666666667;
                }
            }
            else if(mouse_pos.x>= r1920.getGlobalBounds().left &&
                    mouse_pos.x<= r1920.getGlobalBounds().left+r1920.getGlobalBounds().width &&
                    mouse_pos.y>= r1920.getGlobalBounds().top &&
                    mouse_pos.y<= r1920.getGlobalBounds().top+r1920.getGlobalBounds().height
                    && window_value==5)
            {
                if(!Mouse_pressed)
                {
                Mouse_pressed=1;
                window_value=4;
                screen_width = 1920;
                screen_height = 1080;
                scale_factor=1;
                }
            }
            else if(mouse_pos.x>= r2560 .getGlobalBounds().left &&
                    mouse_pos.x<= r2560.getGlobalBounds().left+r2560.getGlobalBounds().width &&
                    mouse_pos.y>= r2560.getGlobalBounds().top &&
                    mouse_pos.y<= r2560.getGlobalBounds().top+r2560.getGlobalBounds().height
                    && window_value==5 )
            {
                if(!Mouse_pressed)
                {
                Mouse_pressed=1;
                window_value=4;
                screen_width = 2560;
                screen_height = 1440 ;
                scale_factor=1.3333;
                }
            }


        }else Mouse_pressed=0;



        if(window_value==6)
        {

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window_value=7;
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

        sf::Time Delta = deltaClock.restart();
        float Second = Delta.asSeconds();

        Time+=Time+Second;
        //p1.Movement(Second, window_value);
        p6.Sound_movement(window_value);
        p1.Movement_Again(Second, window_value);
        p1.Collisions(Second, window_value);
        p4.Movement_T(p1.Position(), Second); // player tracking for texture




        window.clear(sf::Color::Black);



        if(window_value==1) //menu screen
        {
            window.draw(Background);
            window.draw(Start);
            window.draw(Settings);
            window.draw(Exit_Game);
        }
        else if (window_value==2)
        {
            window.draw(Background);
            if(first_save)
                window.draw(New_Game);
            else window.draw(Continue_Game);

            window.draw(Load);
            window.draw(Exit);
        }
        else if (window_value==3)       //pause screen
        {
            window.draw(Background);
            window.draw(Audio);
            window.draw(Graphics);
            window.draw(Exit);
        }
        else if (window_value==4)
        {
            window.draw(Background);
            window.draw(Window_Resize);
            window.draw(Toggle1);
            window.draw(Toggle2);
            window.draw(Exit);

        }
        else if (window_value==5)
        {
            window.draw(Background);
            window.draw(r720);
            window.draw(r1280);
            window.draw(r1920);
            window.draw(r2560);
            window.draw(Exit);
        }

        else if(window_value==6)        //actual game
        {
            if(ambient_playing==0)
            {
                music.play();
                ambient_playing=1;
            }

            window.draw(p5);
            window.draw(p1);
            window.draw(p2);
           // window.draw(p3);
            window.draw(p4);

        }
        else if (window_value==7)
        {

           window.draw(Background);

           window.draw(Exit);
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
