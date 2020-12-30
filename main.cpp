#include "game_init.h"
#include "game.h"
#include "game_close.h"
#include <iostream>


int main( int argc, char* args[] )
{

	Game_Init game_init;   // Creates initial window and asks for the player's name
	
	Game game(game_init);  // Creates a game window and acquires property of certain Game_Init variables
	
	game.game_run();  //  main loop of the game
	
	Game_Close game_close(game, game_init); // Creates the final screen and displays game records
	
	return 0;
}




