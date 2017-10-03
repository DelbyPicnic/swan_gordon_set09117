// (C)2017 Gordon Swan (DELBYPICNIC)
// SET09117 Edinburgh Napier University
// Checkers
#include "checkers.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Piece::Piece(int col, location loca)
{
	// Ensure that the colour value is within the correct range
	if(col < 0 || col > 1){
		throw invalid_argument("Colour incicator must be 0 or 1");
	}else{
		colour = col;
	}
	loc = loca;
	isKing = false;
	isCaptured = false; 
}

