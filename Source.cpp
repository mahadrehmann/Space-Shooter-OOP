#include "game.h"

int main()
{
    Game g;                     //Creating Game object
    g.M->display_Menu();        //Calling menu
    g.start_game();             //Starting the game after menu's execution
    return 0;
}
