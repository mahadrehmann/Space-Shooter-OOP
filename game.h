#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include <iostream>
#include "string.h"
using namespace std;

#include "menu.h"
#include "player.h"
#include "Enemy.h"

const char title[] = "Space Shooter - Mahad";
using namespace sf;


class Game
{
   public:
        Sprite background;             //Game background sprite
        Texture bg_texture;
        Menu * M;                      //Menu
        Player* p;                     //player 

        Enemy * enemies[12];          //Enemies Pointer
        int enemy_count;               //To count number of enemies
        int enemy_reseter;              //Used to reset position of enemies
        int enemy_formation;           //Used to Select Formation of Enemies

        int bomb_timer;                //Timer to control the rate at which enmeies fire

        int score;                     //Integer to store the Score
        string score_string;           //USed when score is to be displayed on Window
        int lives_counter;             //Counter for lives



    Game()
    {
        //Initializing the menu and the player
        M = new Menu;
        p = new Player("img/player_ship.png");

        enemy_count=12;

        //Initializing all enemies:
        for (int i = 0; i < 5; i++)  
        {
            enemies[i] = new Gamma_Invader;
        }
        for (int i = 5; i < 9; i++)
        {
            enemies[i] = new Beta_Invader;
        }
        for (int i = 9; i < 12; i++)
        {
            enemies[i] = new Alpha_Invader;
        } 


        //Gamma Invader/Enemy
        enemies[0]->sprite.setPosition(100, 50);
        enemies[1]->sprite.setPosition(200, 50);
        enemies[2]->sprite.setPosition(300, 50);
        enemies[3]->sprite.setPosition(400, 50);
        enemies[4]->sprite.setPosition(500, 50);

        //Beta Invader/Enemy
        enemies[5]->sprite.setPosition(150, 150);
        enemies[6]->sprite.setPosition(100, 50);
        enemies[7]->sprite.setPosition(450, 150);
        enemies[8]->sprite.setPosition(450, 150);

        //Alpha Invader/Enemy
        enemies[9]->sprite.setPosition(260, 270);
        enemies[10]->sprite.setPosition(360, 270);
        enemies[11]->sprite.setPosition(300, 370);



        for(int i=0;i<enemy_count;i++)    //Setting Enemies Bombs
            enemies[i]->bomb->sprite.setPosition(enemies[i]->sprite.getPosition().x, enemies[i]->sprite.getPosition().y);                  
                        
        enemy_formation=0;
        bomb_timer=0;
        lives_counter=0;
        enemy_reseter=0; 
        score=0;
        score_string="";

        bg_texture.loadFromFile("img/backgroundn.jpg");  //Loading Background
        background.setTexture(bg_texture);
        background.setScale(2, 1.5);
    }


//Main Function to start the Game
void start_game()
{
    if(M->isGameStarted)
    {
        srand(time(0));
        RenderWindow window(VideoMode(780, 780), title);
        Clock clock;
        float timer=0;


//-------------------------------------APPLYING MUSIC AND SOUNDS------------------------------------//  
    Music music,gameover,destroy;
    music.openFromFile("Sounds/Space_Shooter.ogg");
    destroy.openFromFile("Sounds/destroy.wav");
    gameover.openFromFile("Sounds/gameover.ogg");

    music.setLoop(true);  
    music.play();

//-------------------------------------SETTING TEXT ON WINDOW----------------------------------------//  
    Font font;
    font.loadFromFile("SEASRN__.ttf");
    
    Text text;                              //Decalring Text for Writing Lives
    text.setFont(font);
    text.setString("Lives: ");
    text.setCharacterSize(24);
    text.setFillColor(Color::White);
    text.setPosition(50, 20);

    Text text2;                             //Decalring Text for Writing Score
    text2.setFont(font);
    text2.setString("Score: ");
    text2.setCharacterSize(24);
    text2.setFillColor(Color::White);
    text2.setPosition(600, 20);

    Text text3;                             //Decalring Text for Score
    text3.setFont(font);
    
    text3.setCharacterSize(24);
    text3.setFillColor(Color::White);
    text3.setPosition(700, 20);


//-----------------------------MAIN WHILE LOOP STARTS-----------------------------------------//
        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds(); 
            clock.restart();
            timer += time;  

 	        Event e;
 	        
            while (window.pollEvent(e)) 
            {  
                if (e.type == Event::Closed)        // If cross/close is clicked/pressed
                { 
                    music.stop();                   //stop playing the music
                    window.close();                 //close the game  
                }                          	    
            }



//-----------------------------Converting And Diplaying Score as a string-----------------------------------------//
        string score_string= to_string(score);  
        text3.setString(score_string);
      


//////////////////////////-------------MOVEMENT---------------/////////////////////////////////////////

     	if (Keyboard::isKeyPressed(Keyboard::Left)) //If left key is pressed
                p->move("l");    // Player will move to left
                
      	if (Keyboard::isKeyPressed(Keyboard::Right)) // If right key is pressed
                p->move("r");  //player will move to right
                
    	if (Keyboard::isKeyPressed(Keyboard::Up)) //If up key is pressed
                p->move("u");    //playet will move upwards
                
    	if (Keyboard::isKeyPressed(Keyboard::Down)) // If down key is pressed
                p->move("d");  //player will move downwards
                
        if (Keyboard::isKeyPressed(Keyboard::Escape)) // if escape key pressesd then close window
                window.close();

 //---------------------------------------------------------------------------------------------------------//       
	     
	//  Calling functions
	   	
        p->wrap_around();                      // Wrap Around Check
        p->lives_check();                      // To Check and Display Lives Sprite
        p->fire();                             // Firing players bullets
        p->bullet_check();                     //Checks if Bullet is out of screen 
        p->dang->move();                       // Fire Danger meteor

//-------------------------------------------------------------------------------------------//       
        for(int i=0;i<enemy_count;i++)           //To fire the Enemies bombs
        {
            enemies[i]->bomb->move();
        } 
        bomb_timer++;
 
 //-----------------------------------------------------------------------------------------------//

        for(int i=0;i<enemy_count;i++)           //To check if bombs are out of bound
        {
            if( enemies[i]->bomb->sprite.getPosition().y > 780 )
            {
                if(bomb_timer>1200)                  //To Refire the bomb
                {
                    enemies[i]->bomb->sprite.setPosition(enemies[i]->sprite.getPosition().x, enemies[i]->sprite.getPosition().y);                  
                    bomb_timer=0;
                }    
            }
        }


//--------------------------ALL POSSIBLE COLLISIONS DETECTIONS-----------------------------------------------//       
       

        for(int i=0;i<enemy_count;i++)                 //collision detection of PLayer's bullet And Invaders
        {           
            if(  (p->b->sprite.getPosition().x <= enemies[i]->sprite.getPosition().x + 45)  &&  (p->b->sprite.getPosition().x >= enemies[i]->sprite.getPosition().x - 45 )   &&    (p->b->sprite.getPosition().y >= enemies[i]->sprite.getPosition().y -45) && (p->b->sprite.getPosition().y <= enemies[i]->sprite.getPosition().y + 45 )  ) 
            { 
                enemies[i]->sprite.setPosition(-200,-200);
                score+=enemies[i]->getScore();
                destroy.play();
                // destroy.stop();
            }            
        }


            for(int i=0;i<enemy_count;i++)                 //collision detection of PLayer And Alpha Invaders
            {           
                if(  (p->sprite.getPosition().x <= enemies[i]->sprite.getPosition().x + 45)  &&  (p->sprite.getPosition().x >= enemies[i]->sprite.getPosition().x - 45 )   &&    (p->sprite.getPosition().y >= enemies[i]->sprite.getPosition().y -45) && (p->sprite.getPosition().y <= enemies[i]->sprite.getPosition().y + 45 )  ) 
                { 
                    (p->total_lives->lives)=(p->total_lives->lives)-1;
                    p->sprite.setPosition(300,750);
                }            
            }

                for(int i=0;i<enemy_count;i++)                 //collision detection of PLayer And Alpha Invaders Bombs
                {           
                    if(  (p->sprite.getPosition().x <= enemies[i]->bomb->sprite.getPosition().x + 20)  &&  (p->sprite.getPosition().x >= enemies[i]->bomb->sprite.getPosition().x - 20 )   &&    (p->sprite.getPosition().y >= enemies[i]->bomb->sprite.getPosition().y -20) && (p->sprite.getPosition().y <= enemies[i]->bomb->sprite.getPosition().y + 20 )  ) 
                    { 
                        (p->total_lives->lives)=(p->total_lives->lives)-1;
                        p->sprite.setPosition(300,750);
                    }            
                }   

//---------------------------------------------------------------------------------------------------------------------------------------//

                    // for(int i=0;i<enemy_count;i++)                 //collision detection of PLayer's bullet And Beta Invaders
                    // {           
                    //     if(  (p->b->sprite.getPosition().x <= en_B[i].sprite.getPosition().x + 45)  &&  (p->b->sprite.getPosition().x >= en_B[i].sprite.getPosition().x - 45 )   &&    (p->b->sprite.getPosition().y >= en_B[i].sprite.getPosition().y -45) && (p->b->sprite.getPosition().y <= en_B[i].sprite.getPosition().y + 45 )  ) 
                    //     { 
                    //         en_B[i].sprite.setPosition(-200,-200);
                    //         score+=en_B->getScore();
                    //         destroy.play();
                    //         // destroy.stop();
                    //     }            
                    // }


                    //     for(int i=0;i<enemy_count;i++)                 //collision detection of PLayer And Beta Invaders
                    //     {           
                    //         if(  (p->sprite.getPosition().x <= en_B[i].sprite.getPosition().x + 60)  &&  (p->sprite.getPosition().x >= en_B[i].sprite.getPosition().x - 60 )   &&    (p->sprite.getPosition().y >= en_B[i].sprite.getPosition().y -60) && (p->sprite.getPosition().y <= en_B[i].sprite.getPosition().y + 60 )  ) 
                    //         { 
                    //             (p->total_lives->lives)=(p->total_lives->lives)-1;
                    //             p->sprite.setPosition(300,750);
                    //         }            
                    //     }

                    //         for(int i=0;i<enemy_count;i++)                 //collision detection of PLayer And Beta Invaders Bombs
                    //         {           
                    //             if(  (p->sprite.getPosition().x <= en_B[i].bomb->sprite.getPosition().x + 20)  &&  (p->sprite.getPosition().x >= en_B[i].bomb->sprite.getPosition().x - 20 )   &&    (p->sprite.getPosition().y >= en_B[i].bomb->sprite.getPosition().y -20) && (p->sprite.getPosition().y <= en_B[i].bomb->sprite.getPosition().y + 20 )  ) 
                    //             { 
                    //                 (p->total_lives->lives)=(p->total_lives->lives)-1;
                    //                 p->sprite.setPosition(300,750);
                    //             }            
                    //         } 


//------------------------ENEMY FORMATIONS-------------------------------------------------//

        for(int i=0;i<enemy_count;i++)                 //Enemey Position reseter
        {           
            if(enemies[i]->sprite.getPosition().x == -200) 
                enemy_reseter++;
            else
            {
                break;    
            }

            if(enemy_reseter==12)
            {
                enemy_formation++;
                   
                    if (enemy_formation == 1)   // cross formation
                    {
                        p->sprite.setPosition(340, 670);
                        enemies[0]->sprite.setPosition(50, 50);
                        enemies[1]->sprite.setPosition(650, 50);
                        enemies[2]->sprite.setPosition(550, 100);
                        enemies[3]->sprite.setPosition(550, 100);
                        enemies[4]->sprite.setPosition(250, 200);

                        // Beta
                        enemies[5]->sprite.setPosition(450, 200);
                        enemies[6]->sprite.setPosition(350, 300);
                        enemies[7]->sprite.setPosition(250, 400);
                        enemies[8]->sprite.setPosition(450, 400);

                        // Alpha
                        enemies[9]->sprite.setPosition(150, 500);
                        enemies[10]->sprite.setPosition(550, 500);
                        enemies[11]->sprite.setPosition(50, 600);

                        enemy_reseter = 0;
                    }

                   //  rectangle
                    if (enemy_formation == 2)
                    {
                        p->sprite.setPosition(340, 670);

                        // Gamma
                        enemies[0]->sprite.setPosition(100, 50);
                        enemies[1]->sprite.setPosition(200, 50);
                        enemies[2]->sprite.setPosition(300, 50);
                        enemies[3]->sprite.setPosition(400, 50);
                        enemies[4]->sprite.setPosition(400, 50);

                        // Beta
                        enemies[5]->sprite.setPosition(400, 150);
                        enemies[6]->sprite.setPosition(400, 280);
                        enemies[7]->sprite.setPosition(300, 280);
                        enemies[8]->sprite.setPosition(200, 280);

                        // Alpha
                        enemies[9]->sprite.setPosition(100, 300);
                        enemies[10]->sprite.setPosition(100, 200);
                        enemies[11]->sprite.setPosition(100, 200);
                        enemy_reseter = 0;
                    }

                    // circle
                    if (enemy_formation == 3)
                    {

                        p->sprite.setPosition(340, 670);
                        enemies[0]->sprite.setPosition(250, 20);
                        enemies[1]->sprite.setPosition(150, 50);
                        enemies[2]->sprite.setPosition(340, 50);
                        enemies[3]->sprite.setPosition(100, 100);
                        enemies[4]->sprite.setPosition(390, 100);

                        // // Beta
                        enemies[5]->sprite.setPosition(130, 170);
                        enemies[6]->sprite.setPosition(380, 170);
                        enemies[7]->sprite.setPosition(150, 240);
                        enemies[8]->sprite.setPosition(350, 240);

                        // // Alpha
                        enemies[9]->sprite.setPosition(250, 300);
                        enemies[10]->sprite.setPosition(250, 300);
                        enemies[11]->sprite.setPosition(250, 300);
  
                        enemy_reseter = 0;
                    }
                    // Heart
                    if (enemy_formation == 4)
                    {
                        p->sprite.setPosition(600, 670);

                        enemies[0]->sprite.setPosition(300, 120);
                        enemies[1]->sprite.setPosition(190, 50);
                        enemies[2]->sprite.setPosition(400, 50);
                        enemies[3]->sprite.setPosition(150, 120);
                        enemies[4]->sprite.setPosition(440, 120);

                        // // Beta
                        enemies[5]->sprite.setPosition(180, 190);
                        enemies[6]->sprite.setPosition(430, 190);
                        enemies[7]->sprite.setPosition(200, 260);
                        enemies[8]->sprite.setPosition(400, 260);

                        // // Alpha
                        enemies[9]->sprite.setPosition(300, 340);
                        enemies[10]->sprite.setPosition(300, 340);
                        enemies[11]->sprite.setPosition(300, 340);

                        enemy_reseter = 0;
                    }

                    // Diamond
                    if (enemy_formation == 5)
                    {

                        p->sprite.setPosition(550, 650);
                        enemies[0]->sprite.setPosition(320, 50);
                        enemies[1]->sprite.setPosition(220, 120);
                        enemies[2]->sprite.setPosition(410, 120);
                        enemies[3]->sprite.setPosition(135, 220);
                        enemies[4]->sprite.setPosition(490, 220);

                        // // // Beta
                        enemies[5]->sprite.setPosition(135, 320);
                        enemies[6]->sprite.setPosition(490, 320);
                        enemies[7]->sprite.setPosition(210, 400);
                        enemies[8]->sprite.setPosition(420, 400);

                        // // // Alpha
                        enemies[9]->sprite.setPosition(310, 470);
                        enemies[10]->sprite.setPosition(310, 470);
                        enemies[11]->sprite.setPosition(310, 470);

                        enemy_reseter = 0;
                    }
                    if (enemy_formation == 6)
                    {
                        p->sprite.setPosition(600, 670);
                        // Triangle Filled

                        //   Gamma
                        enemies[0]->sprite.setPosition(100, 50);
                        enemies[1]->sprite.setPosition(200, 50);
                        enemies[2]->sprite.setPosition(300, 50);
                        enemies[3]->sprite.setPosition(400, 50);
                        enemies[4]->sprite.setPosition(500, 50);

                        // Beta
                        enemies[5]->sprite.setPosition(150, 150);
                        enemies[6]->sprite.setPosition(250, 150);
                        enemies[7]->sprite.setPosition(350, 150);
                        enemies[8]->sprite.setPosition(450, 150);

                        // Alpha
                        enemies[9]->sprite.setPosition(260, 270);
                        enemies[10]->sprite.setPosition(360, 270);
                        enemies[11]->sprite.setPosition(300, 370);
                        enemy_reseter = 0;
                    }
                    if (enemy_formation == 7)
                    {
                        p->sprite.setPosition(600, 670);

                        // HEART Filled
                        enemies[0]->sprite.setPosition(300, 120);
                        enemies[1]->sprite.setPosition(190, 50);
                        enemies[2]->sprite.setPosition(400, 50);
                        enemies[3]->sprite.setPosition(150, 120);
                        enemies[4]->sprite.setPosition(440, 120);

                        // // Beta
                        enemies[5]->sprite.setPosition(180, 190);
                        enemies[6]->sprite.setPosition(430, 190);
                        enemies[7]->sprite.setPosition(200, 260);
                        enemies[8]->sprite.setPosition(400, 260);

                        // // Alpha
                        enemies[9]->sprite.setPosition(300, 340);
                        enemies[10]->sprite.setPosition(300, 190);
                        enemies[11]->sprite.setPosition(300, 275);

                        enemy_reseter = 0;
                        enemy_formation =0;
                    }
            } 
        }       
        enemy_reseter=0;
    

//--------------------------------------------------------------------------------------------------//

    if (p->total_lives->lives == 0)
    {
        music.stop();
        gameover.play();

        window.close();
        M->gameOver();
    }    
//--------------------------------------------------------------------------------------------------//


     	window.clear(Color::Black);             //clears the screen
        window.draw(background);                // setting background
        window.draw(p->sprite);                 // setting player on screen
        window.draw(p->b->sprite);              //setting bullet on screen     
        window.draw(p->dang->sprite);           //setting danger on screen
        window.draw(p->total_lives->sprite);    //setting lives count on screen

        for(int i=0;i<enemy_count;i++)          //setting enemeies on the screen
        {
            window.draw(enemies[i]->sprite);
        }

        for(int i=0;i<enemy_count;i++)          //setting enemeies bomb on the screen
        {
            window.draw(enemies[i]->bomb->sprite);            
        }
       
        window.draw(text);
        window.draw(text2);
        window.draw(text3);
	    window.display();                   //Displying all the sprites
           
        }


    }
}

    ~Game()   //Destructor
    {
        if(M!=NULL)
        {
            delete M; 
            M=NULL;
        }

        if(p!=NULL)
        {
            delete p;
            p=NULL;
        }  

        for(int i=0;i<enemy_count;i++)
        {
            if(enemies[i] != NULL)    
            {
                delete enemies[i];
                enemies[i]=NULL;
            }       
        }
    }


};

