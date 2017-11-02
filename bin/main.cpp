// (C)2017 Gordon Swan (DELBYPICNIC)
// SET09117 Edinburgh Napier University
// Checkers

// INFORMATION
// 0 == BLACK == TOP
// 1 == WHITE == BOTTOM

#include <iostream>
#include <vector>
#include <string>
#include "checkers.h"

using namespace std;
// TEMP - Moving this into a class
// Modify this function to accept a 2D vector of postions (possibly a pointer to)


int main(int argv, char* argc[])
{	
	// Create new instance of game
	// Init new game
	// Create gameloop (MUST NOT DIE)
	// Parse user input

	// System Loop: Will start a new game should the Game Loop die
	while(true){
		Game* m_game = new Game();
		m_game->initGame();

		// Game Loop: Will collect user input and update the GUI
		while(true){
			m_game->drawState();
			m_game->playMove(m_game->getUsrInput());
			m_game->drawState();

			break; //TEMP
		}
	}
}