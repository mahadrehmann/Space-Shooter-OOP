class Add_on
{
public:
    Texture tex;
    Sprite sprite;
    float speed = 0.1;

    virtual ~Add_on() {} // Destructor added to release resources properly
};
//--------------------------------------------------------------------------//
class Danger : public Add_on
{
public:    
    Danger()
    {
        tex.loadFromFile("img/PNG/Meteors/meteorBrown_big4.png");
        sprite.setTexture(tex);
        sprite.setScale(0.6, 0.6);
    }

    void move()
    {
        float delta_x = 0, delta_y = +1;
       
        delta_x *= speed;
        delta_y *= speed;

        sprite.move(delta_x, delta_y);
    }
};

//----------------------------------------------------------------------//
class Lives : public Add_on
{
public:
    int lives;
   
    Lives()
    {   
        tex.loadFromFile("img/PNG/UI/numeral3.png");
        sprite.setTexture(tex);
        sprite.setScale(1, 1);   
        sprite.setPosition(140, 22);     
        lives = 3;     
    }
};
