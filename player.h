#include <SFML/Graphics.hpp> 
#include<string.h>
#include <time.h>
#include<cstdlib>
using namespace sf;
#include "Bullet.h"
#include "Add_on.h"



class Player
{
  public:
    Texture tex;
    Sprite sprite;
    
    Bullet *b;
    
    Danger* dang;

    Lives* total_lives;

    float speed=0.1;
    int x,y;

    bool change_skin1,change_skin2;
 
    Player(std::string png_path)
    {
        srand(time(0));

        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        x=340;y=650;
        sprite.setPosition(x,y);
        sprite.setScale(0.75,0.75);

        b=new Bullet;  
        b->sprite.setPosition (this->sprite.getPosition().x, this->sprite.getPosition().y); 
        
        dang= new Danger;
        dang->sprite.setPosition( (rand() %780),0);
        
        total_lives= new Lives;

        change_skin1=0;
        change_skin2=0;
    }

//----------------------------------------------------------------------------------------------//

    void fire()
    {
        b->move();          //Calling bullets move() function
    }

//------------------------------------------------------------------------------------------------//

    void bullet_check()
    {
        if(b->sprite.getPosition().y <0 )
            b->sprite.setPosition (this->sprite.getPosition().x, this->sprite.getPosition().y); 
    }
//----------------------------------------------------------------------------------------------------//    
    void move(std::string s)
    {
        float delta_x=0,delta_y=0;
        
       if(s=="l")
	       delta_x=-1;//move the player left
       else if(s=="r")
	       delta_x=1;//move the player right

        if(s=="u")
	       delta_y=-1;
        else if(s=="d")
	       delta_y=1;

        delta_x*=speed;
        delta_y*=speed;
	
       sprite.move(delta_x, delta_y);
    }

//----------------------------------------------------------------------------------------//

    void wrap_around()
    {
        if(sprite.getPosition().x <0 )             
            sprite.setPosition(700,sprite.getPosition().y);

        if(sprite.getPosition().x >740 )            
            sprite.setPosition(0,sprite.getPosition().y);  

        if(sprite.getPosition().y <0 )            
            sprite.setPosition(sprite.getPosition().x,720);            

        if(sprite.getPosition().y >740 )            
            sprite.setPosition(sprite.getPosition().x,0);
    }

//------------------------------------------------------------------------------------------//

    void lives_check()
    {
        if(change_skin1==0)
        {
            if(total_lives->lives == 2)
            {
                total_lives->tex.loadFromFile("img/PNG/UI/numeral2.png");
                tex.loadFromFile("img/PNG/playerShip2_orange.png");
                change_skin1=1;   //This will ensure it doesnt run again
            } 
        }
       
        if(change_skin2==0)
        {
            if(total_lives->lives == 1)
            {
                total_lives->tex.loadFromFile("img/PNG/UI/numeral1.png");
                tex.loadFromFile("img/PNG/playerShip2_red.png");
                change_skin2=1;
            } 
        }    
    }
//--------------------------------------------------------------------//
   ~Player()
    {
        if(b!=NULL)
        {
            delete b; b=NULL;
        }
        if(dang!=NULL)
        {    
            delete dang; dang=NULL;
        }
        if(total_lives!=NULL)
        {
            delete total_lives; total_lives=NULL;
        }   
    } 
};

