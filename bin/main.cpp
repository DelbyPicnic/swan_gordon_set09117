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

int main(int argv, char* argc[])
{	
	point loc;
	loc.x = 1;
	loc.y = 1;

	Position* pos = new Position(1);
	Piece* pie = new Piece(1, loc);
	pos->setPiece(pie);

	cout << pos->getPiece()->getLocation().x << endl;
}