

#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <sstream>
#include <conio.h>
#include <thread>
#include <chrono>
#include <list>
#include <string>
#include <cstring>
#include <Windows.h>
#include "Function.h"
#include <iostream>

using namespace sf;
using namespace std;
using namespace Engine;

struct point
{
    int x,y;
};

const string PathImageBackground = "Resource/Images/background/";
const string PathImageDoodle = "Resource/Images/doodle/";
const string PathImagePlat = "Resource/Images/plat/";
const string PathImageButton = "Resource/Images/button/";


const string File = "Resource/File/HighScore.txt";
const string Fonts = "Resource/Fonts/al-seana.ttf";
const string Musics = "Resource/Musics/";

unsigned long long ReadFile()
{
    ifstream Read;
    Read.open(File);
    unsigned int score;
    Read >> score;
    Read.close();
    return score;
}

void WriteFile(unsigned long long score)
{
    ofstream Write;
    Write.open(File);
    Write.clear();
    Write << score;
    Write.close();
}


void PlayGame(RenderWindow &window)
{
    Clock Clock; // starts the clock
    if (Keyboard::isKeyPressed(Keyboard::Escape)) return;
    srand(time(0));
    Texture background, plat, doodle, dead, background2, background3, doodle2, doodle3;
    background.loadFromFile(PathImageBackground + "background_simple.png");
    background2.loadFromFile(PathImageBackground + "background_vam.png");
    background3.loadFromFile(PathImageBackground + "background_soccer.png");

    plat.loadFromFile(PathImagePlat + "plat.png");
    doodle.loadFromFile(PathImageDoodle + "doodleSimple.png");
    doodle2.loadFromFile(PathImageDoodle + "doodleNinja.png");
    doodle3.loadFromFile(PathImageDoodle + "doodleFrozen.png");

    dead.loadFromFile(PathImageBackground +"game_over.png");
    Sprite Background(background), Plat(plat), Doodle(doodle), gameOver(dead);
    Doodle.setPosition(0, 524);


//	Text Score;
//	Score.setFont(font);
//	Score.setFillColor(Color::Red);
//	Score.setPosition(5,10);
//	Score += 1.f/60.f;
//	Score.setString("Score: " + to_string)

    SoundBuffer backgroundSound, jumpStep, die;
    backgroundSound.loadFromFile(Musics + "Wing.wav");
    jumpStep.loadFromFile(Musics + "Point.wav");
    die.loadFromFile(Musics + "Die.wav");
    Sound BackgroundSound(backgroundSound),
          Jump(jumpStep), Die(die);
    BackgroundSound.setBuffer(backgroundSound);

    Music musicBackgroud,dieMusic;
    if (!musicBackgroud.openFromFile(Musics + "battle.wav"))
        return;
    if (!dieMusic.openFromFile(Musics + "game_over.wav"))
        return;
    musicBackgroud.play();
    musicBackgroud.setLoop(true);


    //score





    point platform[20];

    for (int i=0; i<10; i++)
    {
        platform[i].x=rand()%(400-25);
        platform[i].y=rand()%(533-27);
    }

    int x=100,y=100, h=200;

    float dx=0,dy=0;

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();
        }
        unsigned int score = 0;

        if (Keyboard::isKeyPressed(Keyboard::Right)) x+=7;

        if (Keyboard::isKeyPressed(Keyboard::Left)) x-=7;
        dy += 0.2;
        y += dy;

        // score += 60.f;



        if (y<h)
            for (int i=0; i<50; i++)
            {
                y=h;
                platform[i].y=platform[i].y-dy;
                if (platform[i].y>533)
                {
                    platform[i].y=0;
                    platform[i].x=rand()%400;
                }
            }

        for (int i=0; i<50; i++)
            if ((x+50>platform[i].x) && (x+20<platform[i].x+68)
                    && (y+70>platform[i].y) && (y+70<platform[i].y+14) && (dy>0))
            {
                dy=-9;
            }
        int Time = Clock.getElapsedTime().asMilliseconds();
        cout << Time << endl;
        score= Time;
        int time2 = Clock.getElapsedTime().asSeconds();
        if (time2 > 10 && time2 % 15 == 0) {
                Background.setTexture(background3);
                Doodle.setTexture (doodle2);

                std::cout << "Change Texture!" << std::endl;
        }
        if (time2 > 10 && time2 % 30 == 0) {
                Background.setTexture(background2);
                Doodle.setTexture (doodle3);

                std::cout << "Change Texture!" << std::endl;
        }

        if (score > ReadFile()) WriteFile(score);

        Text Score;

//     float Time = Clock.getElapsedTime();
        //cout << elapsed.asSeconds() << endl;

        Font font;
        font.loadFromFile(Fonts);
        Score.setFont(font);
        Score.setFillColor(Color::Blue);
        Score.setStyle(Text::Bold);
        Score.setPosition(25,10);
        Score.setCharacterSize(30);
        Score.setString(Engine::int_to_string(score));
        //score += 1.f/60.f;

        //cout<<score;}
//    Score.setString(to_string(score));

        Doodle.setPosition(x,y);
        window.draw(Background);
        window.draw(Doodle);
        window.draw(Score);

        for (int i=0; i<10; i++)
        {
            Plat.setPosition(platform[i].x,platform[i].y);
            window.draw(Plat);
        }



//        if (score = 2)
//        {
//            window.draw(Background2);
//            window.draw (Doodle2);
//            window.display();
//



        window.display();

        //gameOver
        if (y>500)
        {
            musicBackgroud.stop();
            dieMusic.play();
            std::this_thread::sleep_for(std::chrono::milliseconds(500));


            window.clear();
            window.draw(gameOver);
            window.display();
            std::this_thread::sleep_for(std::chrono::milliseconds(5000));

            return;
        }
    }
}


void Menu(RenderWindow &window)
{
    unsigned long long score = ReadFile();
    Text Score;

//     float Time = Clock.getElapsedTime();
        //cout << elapsed.asSeconds() << endl;

    Font font;
    font.loadFromFile(Fonts);
        Score.setFont(font);
        Score.setFillColor(Color::Blue);
        Score.setStyle(Text::Bold);
        Score.setPosition(200,480);
        Score.setCharacterSize(30);
        Score.setString("High Score: " + Engine::int_to_string(score));
    Texture background;
    background.loadFromFile(PathImageBackground + "background_main.png");
    Sprite Background(background);
    Texture play, x;
    play.loadFromFile(PathImageButton + "PlayButton.png");
    x.loadFromFile(PathImageButton + "exit.png");
    Music music;
    if (!music.openFromFile(Musics + "opening.wav"))
        return;
    SoundBuffer openSound;
    if (!openSound.loadFromFile(Musics + "meow.wav"))
        cout<<"Can't load meow";
    Sound OpenSound;
    OpenSound.setBuffer(openSound);
    music.play();
    music.setLoop(true);
    Sprite Play(play), GetOut(x);
    Play.setOrigin(52, 29);
    GetOut.setOrigin(60, 20);
    Play.setPosition(130, 250);
    GetOut.setPosition(140, 340);
    GetOut.setColor(Color::White);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) window.close();
        }
        window.clear();
//		    window.draw (gameOver);

        window.draw(Background);
        window.draw(Play);
        window.draw(GetOut);
        window.draw(Score);

        window.display();
        if (Keyboard::isKeyPressed(Keyboard::Escape)) return;

        if (Mouse::isButtonPressed(Mouse::Left)
                && Mouse::getPosition(window).x >= 140
                && Mouse::getPosition(window).x <= 242
                && Mouse::getPosition(window).y >= 220
                && Mouse::getPosition(window).y <= 279)
        {
            music.stop();
            OpenSound.play();
            PlayGame(window);
        }


        if (Mouse::isButtonPressed(Mouse::Left)
                && Mouse::getPosition(window).x >= 130
                && Mouse::getPosition(window).x <= 250
                && Mouse::getPosition(window).y >= 330
                && Mouse::getPosition(window).y <= 370) return ;
    }
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    RenderWindow window(VideoMode(400, 533), "Doodle Jump!", Style::Titlebar);
    window.setFramerateLimit(60);
    //Image Icon;
    //Icon.loadFromFile(PathImage + "icon.ico");
//    window.setIcon(Icon.getSize().x, Icon.getSize().y, Icon.getPixelsPtr());
    Menu(window);
    return 0;
}


