// (C)2017 Gordon Swan (DELBYPICNIC)
// SET09117 Edinburgh Napier University
// Checkers

// INFORMATION
// 0 == BLACK == TOP
// 1 == WHITE == BOTTOM

#include "checkers.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Piece::Piece(int col, point loc)
{
	// Ensure that the colour value is within the correct range
	if(col < 0 || col > 1){
		throw invalid_argument("Colour incicator must be 0 or 1");
	}else{
		colour = col;
	}
	location = loc;
	isKing = false;
	isCaptured = false; 
}
void Piece::mkKing()
{
	isKing = true;
}
void Piece::mkCapture()
{
	isKing = false;
	isCaptured = true;
	
	// Set capture location for all pieces to -1 
	location.x = -1;
	location.y = -1;
}

void Position::setPiece(Piece* p)
{
	piece = p;

}

Move::Move(Piece* p, point d)
{
	piece = p;
	dest = d;

	// Distance must be calculated
	int dx = (piece->getLocation().x - dest.x) * 1;
	int dy = (piece->getLocation().y - dest.y) * 1;
	if(dx == dy){
		if(dx < 3 && dx > 0){
			distance = dx;
		}
	}

	// Calculate Relative Direction
	int y = (piece->getLocation().y - dest.y);

	if(piece->getColour() == 0){
		// Piece is black
		// Relative forward is down / negative y
		if(y < 0){direction = "FORWARD";}
		else if(y > 0){direction = "BACKWARD";}
	}
	else if(piece->getColour() == 1){
		// Piece is white
		// Relative forward direction is up / posative y
		if(y > 0){direction = "FORWARD";}
		else if(y < 0){direction = "BACKWARD";}
	}
	// Validate the movement
	if(direction == "BACKWARD" && piece->getKing() == false){
		throw invalid_argument("Only King pieces may move backward");
	}

	// Request a value for this move from the AI
	value = 1; // TEMP
		// Move evaluation will be bolted on at a later stage, 
		// there will be a call to an AI API here once i've written it.
		// Evaluation will run from 1 to 5, with 1 being the worst and 5
		// being the best.
}