class Bomb
{
 public:
    Texture tex;
    Sprite sprite;
    float speed=0.1;

    Bomb()
    {
        tex.loadFromFile("img/enemy_laser.png");
        sprite.setTexture(tex);
        sprite.setScale(0.6,0.6);
    }
    void move()
    {
        float delta_x=0,delta_y=+1;
       
        delta_x*=speed;
        delta_y*=speed;

       sprite.move(delta_x, delta_y);

    }

};
