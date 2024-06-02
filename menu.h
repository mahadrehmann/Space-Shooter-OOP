#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "iostream"
using namespace std;
using namespace sf;
const char titlee[] = "OOP-Project, Spring-2023";
class Menu
{
public:
    sf::RenderWindow window;
    sf::Font font;
    bool isGameStarted;
    bool isResume,Ismusic;
    Sprite  MENN, Instruct, hisc, onebadge, secbadge, thibadge, endscreen;       // Game background sprite
    Texture MENtex, intrttex, hisctex, obadgetex, sbadgetex, tbadgetex, endtex;  // Game background Textures

    Menu()
    {
        //Loading all sprites
        font.loadFromFile("OpenSans-Regular.ttf");
        isGameStarted = false;
        isResume = false;
        Ismusic = true;
        intrttex.loadFromFile("img/instructions.jpg");
        Instruct.setTexture(intrttex);
        Instruct.setScale(0.7, 0.82);

        hisctex.loadFromFile("img/highscore.jpg");
        hisc.setTexture(hisctex);
        hisc.setScale(1, 1.74);

        MENtex.loadFromFile("img/Image1.jpg");
        MENN.setTexture(MENtex);
        MENN.setScale(0.7, 0.82);

        obadgetex.loadFromFile("img/first.png");
        onebadge.setTexture(obadgetex);
        onebadge.setScale(0.007,0.007);

        sbadgetex.loadFromFile("img/second.png");
        secbadge.setTexture(sbadgetex);
        secbadge.setScale(0.12,0.12);

        tbadgetex.loadFromFile("img/third.png");
        thibadge.setTexture(tbadgetex);
        thibadge.setScale(0.05,0.045);

        endtex.loadFromFile("img/black_bg.png");
        endscreen.setTexture(endtex);
        endscreen.setScale(2, 2);
    }

    ~Menu()
    {
        //delete high_Score;
    }

    void display_Menu()
    {
        srand(time(0));
        RenderWindow window(VideoMode(880, 880), titlee);
        
        //Initialize the font and Music
        Font font;
        font.loadFromFile("OpenSans-Regular.ttf");
        Music music;
        music.openFromFile("Sounds/Space_Shooter.ogg");
        
        if(Ismusic== false)
        {
            music.pause();
        }
        else if(Ismusic==true)
        {
            music.play();
        }

        //Menu actions
        Text strt("Press S to start Game\nE to Exit the Game\nI to view instructions\nPress H to view High Scores", font, 20);
        strt.setPosition(300, 50);
        strt.setFillColor(Color::Cyan);
        strt.setOutlineThickness(3);

        strt.setPosition(0, 30);

        Text startGameText("Start Game", font, 32);
        startGameText.setPosition(330, 230);
        startGameText.setFillColor(Color::Magenta);
        startGameText.setOutlineThickness(3);

        Text exitText("Exit", font, 32);
        exitText.setPosition(330, 280);
        exitText.setFillColor(Color::Magenta);
        exitText.setOutlineThickness(3);

        Text instructionsText("Instructions", font, 32);
        instructionsText.setPosition(330, 330);
        instructionsText.setFillColor(Color::Magenta);

        instructionsText.setOutlineThickness(3);

        Text instructions("How to play:\n\nUse the arrow keys to move your spaceship.\nPress the spacebar to Pause the game.\nCollect power-ups to upgrade your weapons.\n\nGood luck, pilot!", font, 20);
        instructions.setPosition(100, 250);
        instructions.setFillColor(Color::Cyan);
        instructions.setOutlineThickness(3);
        Text inst2("Press Esc to go back to menu", font, 14);
        inst2.setPosition(0, 10);
        inst2.setFillColor(Color::Cyan);
        inst2.setOutlineThickness(3);

        Text highScoreTitle("High Scores", font, 32);
        highScoreTitle.setPosition(330, 380);//(330, 430);
        highScoreTitle.setFillColor(Color::Magenta);
        highScoreTitle.setOutlineThickness(3);

        Text Resume("Resume Game", font, 32);
        Resume.setPosition(330, 180);
        Resume.setFillColor(Color::Magenta);
        Resume.setOutlineThickness(3);

        //Main Menu Loop
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (Keyboard::isKeyPressed(Keyboard::S))
                    isGameStarted = true;
                if (Keyboard::isKeyPressed(Keyboard::C))
                    {
                        isGameStarted = true;
                        window.close();
                        Ismusic = true;
                    }
                if (Keyboard::isKeyPressed(Keyboard::E))
                {
                    isGameStarted = false;
                  
                    window.close();
                }
                if (Keyboard::isKeyPressed(Keyboard::I))
                {
                    window.clear();
                    window.draw(Instruct);
                    window.draw(instructions);
                    window.draw(inst2);
                    window.display();
                    while (true)
                    {
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                            if (Keyboard::isKeyPressed(Keyboard::Escape))
                            {
                                break;
                            }
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Escape))
                        {
                            break;
                        }
                    }
                }
                if (Keyboard::isKeyPressed(Keyboard::H))
                {

                    window.clear();

                    // Display the high scores
                    int yPos = 360;

                    window.draw(hisc);
                 
                    onebadge.setPosition(165,355);
                    secbadge.setPosition(165,385);
                    thibadge.setPosition(171,417);
                    window.draw(onebadge);
                    window.draw(secbadge);
                    window.draw(thibadge);
                    window.display();
                    while (true)
                    {
                        sf::Event event;
                        while (window.pollEvent(event))
                        {
                            if (Keyboard::isKeyPressed(Keyboard::Escape))
                            {
                                break;
                            }
                        }
                        if (Keyboard::isKeyPressed(Keyboard::Escape))
                        {
                            break;
                        }
                    }
                }
            }

            window.clear();

            window.draw(MENN);
                if(isResume==true)
                {
                    window.draw(Resume);

                }

            window.draw(startGameText);
            window.draw(exitText);
            window.draw(instructionsText);
            window.draw(strt);

            window.draw(highScoreTitle);

            if (isGameStarted)
            {
                window.close();
            }

            window.display();
        }
    }

    void gameOver()
    {
        srand(time(0));
        RenderWindow window(VideoMode(500, 500), titlee);
        Font font;
        font.loadFromFile("OpenSans-Regular.ttf");

        Text startGameTex("GAME OVER!", font, 50);
        startGameTex.setPosition(110, 170);
        startGameTex.setFillColor(Color::Blue);
        startGameTex.setOutlineColor(Color::White);
        startGameTex.setOutlineThickness(3);

        Text exitText("Press E to Exit!", font, 50);
        exitText.setPosition(100, 300);
        exitText.setFillColor(Color::Blue);
        exitText.setOutlineColor(Color::White);
        exitText.setOutlineThickness(3);

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }

                if (Keyboard::isKeyPressed(Keyboard::R))
                {
                    isGameStarted = true;
                }
                if (Keyboard::isKeyPressed(Keyboard::E))
                {
                    isGameStarted = false;
                    window.close();
                }
            }

            window.clear();

            window.draw(endscreen);
            window.draw(startGameTex);
            window.draw(exitText);
            window.display();
        }
    }
};
