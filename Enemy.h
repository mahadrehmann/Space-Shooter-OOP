#include "Bomb.h"

class Enemy
{ 
public:
    Texture tex;
    Sprite sprite;
    Bomb* bomb;

    Enemy(std::string png_path)
    {
        tex.loadFromFile(png_path);
        sprite.setTexture(tex);
        sprite.setScale(0.5, 0.5);
        bomb = new Bomb;
    }


    virtual int getScore()=0;


    virtual ~Enemy()
    {
        delete bomb;
    }
};

//-----------------------------------------------------------------//

class Invader : public Enemy
{
public:
    Invader( std::string png_path) : Enemy(png_path) {}

    virtual int getScore()=0;
};

//----------------------------------------------------------------------//
class Alpha_Invader : public Invader
{
public:
    Alpha_Invader(): Invader("img/enemy_1.png"){}

    int getScore()
    {
        return 10;
    }
};

//----------------------------------------------------------------//
class Beta_Invader : public Invader
{
public:
    Beta_Invader() : Invader("img/enemy_2.png"){}

    int getScore()
    {
        return 20;
    }    
};

//---------------------------------------------------------------------------//

class Gamma_Invader : public Invader
{
public:
    Gamma_Invader() : Invader("img/enemy_3.png")
    {
        sprite.setScale(0.4, 0.4);

    }
   
    int getScore()
    {
        return 30;
    }
};

///////////////////////////////////////////////////////////////////////////////////////

// class Monster : public Enemy
// {
// public:
//     Monster()
//     {
         
//     }
// };

// ///////////////////////////////////////////////////////////////////////////////

// class Dragon : public Enemy
// {
// public:
//     Dragon()
//     {
         
//     }
// };
