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

	Position* pos = new Position();

	Game* m_game = new Game();
	m_game->drawState();
}