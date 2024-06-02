class Bullet
{
   public:
          
    Texture tex;
    Sprite sprite;
    float speed=0.4;
    int x,y;
 
    Bullet()  
    {
        tex.loadFromFile("img/PNG/Lasers/laserBlue01.png"); 
        sprite.setTexture(tex);
        sprite.setScale(0.75,0.75);
    } 
    
    void move()
    {
        float delta_x=0,delta_y=-1;
       
        delta_x*=speed;
        delta_y*=speed;

       sprite.move(delta_x, delta_y);

    }   

    
        
};

