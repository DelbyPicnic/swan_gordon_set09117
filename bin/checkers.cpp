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

void Position::setColour(int c)
{
	if(c < 0 || c > 1){
		throw invalid_argument("Colour incicator must be 0 or 1");
	}else{
		colour = c;
	}
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

Game::Game()
{
	// Draw welcome message for user
	cout << "\n\nC++ Checkers Framework. (C)2017 Gordon Swan.\nSET09117 - Algorithms and Data Structures\n\n" << endl;

	bool notSelected = true;

	while(notSelected){
		// Get game type information
		cout << "OPTIONS: (Enter a Number)\n[1] Player vs Player\n[2] Player vs Computer\n[3] Computer vs Computer\n[4] Quit\n" << endl;
		string usrInp;
		getline(cin,usrInp);

		try{
			switch(stoi(usrInp, nullptr, 10)){
				case 1: gameMode = 1;
						notSelected = false;
						cout << "Gamemode One Selected...\n" << endl;
						break;
				case 2: gameMode = 2;
						notSelected = false;
						cout << "Gamemode Two Selected...\n" << endl;
						break;
				case 3: gameMode = 3;
						notSelected = false;
						cout << "Gamemode Three Selected...\n" << endl;
						break;
				case 4: cout << "Goodbye" << endl;
						exit(0);
						break;
			}
		}catch(...){
			cout << "Please enter a number... (Argument Exception)\n" << endl;
		}
	}
}

// Find all moves for all pieces of a particular side and return as a vector 
vector<Move> Game::getMoves()
{
	//use push backs
}

// Find all moves for a specified piece and return as a vector
vector<Move> Game::getMoves(Piece* p)
{
	//use push backs
}

void Game::initGame()
{
	// Initialise the gamestate
	board.resize( 8, vector<Position>(8));

	// Init all board locations with the correct colour
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(i % 2 == 0){
				if(j % 2 == 0){
					// 0
					board[j][i].setColour(1);
				}else{
					// 1
					board[j][i].setColour(0);
				}
			}else{
				if(j % 2 == 0){
					// 1
					board[j][i].setColour(0);
				}else{
					// 0
					board[j][i].setColour(1);
				}
			}	
		}
	}

	// Init board with pieces on the first and last three rows.
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j].getColour() == 0){
				point loc;
				loc.x = j;
				loc.y = i;
				board[i][j].setPiece(new Piece(0, loc));
			}
		}
	}
	for(int i = 5; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j].getColour() == 0){
				point loc;
				loc.x = j;
				loc.y = i;
				board[i][j].setPiece(new Piece(1, loc));
			}
		}
	}
}

bool Game::chkForWinner()
{
	// for all positions on the board, if the position has a piece, get the piece
	// colour, if the colour has not yet been found, mark it as found.
	bool foundBlack = false;
	bool foundWhite = false;

	for(int i = 0; i < 8; i++){
		for(auto &j : board[i]){
			if(j.getPiece() != NULL){
				if(j.getPiece()->getColour() == 0){
					foundBlack = true;
				}else if(j.getPiece()->getColour() == 1){
					foundWhite = true;
				}
			}
			if(foundBlack || foundWhite){
				// If both colours have been found in the middle of a search, no 
				// need to continue searching.
				return false;
			}
		}
	}

	if(foundBlack == false || foundWhite == false){
		// One colour has not been found, someone has won.
		return true;
	}
	return false; // 'May reach end of non-void function' warning prevention 
}

void Game::chkForKing()
{
	// for each side, if there's an opponent piece at said side, and 
	// it's not already king then make it king.

	for(auto &b : board[0]){
		// check for white pieces on black side
		if(b.getPiece() != NULL){
			if(b.getPiece()->getColour() == 1 && b.getPiece()->getKing() == false){
				b.getPiece()->mkKing();
			}
		}
	}
	for(auto &w : board[7]){
		// check for black pieces at white side
		if(w.getPiece() != NULL){
			if(w.getPiece()->getColour() == 0 && w.getPiece()->getKing() == false){
				w.getPiece()->mkKing();
			}
		}
	}
}

Move* Game::getUsrInput()
{
	// TEMP - FOR COMPILER SAKE
	point loc;
	loc.x = 2;
	loc.y = 3;
	Move* mv = new Move(board[2][1].getPiece(), loc);
	return mv;
}

void Game::playMove(Move* m)
{
	point curPos = m->getPiece()->getLocation();
	point newPos = m->getDestination();

	if(board[newPos.y][newPos.x].getPiece() == NULL){
		board[newPos.y][newPos.x].setPiece(board[curPos.y][curPos.x].getPiece());
		board[curPos.y][curPos.x].setPiece(NULL);
	}else{
		throw invalid_argument("Invalid move detected: Destination is occupied");
	}
}

void Game::drawState()
{
	cout << "    A   B   C   D   E   F   G   H \n\n";
	// Standard loop with accumulator for rendering rows
	for(int i = 0; i < 8; i++){
		string boxTop;
		string topRow;
		string bottomRow;
		
		for(auto &j : board[i]){

			if(j.getPiece() != NULL){
				if(j.getPiece()->getColour() == 0){
					if(j.getPiece()->getKing()){
						boxTop = " B ";
					}else{
						boxTop = " b ";
					}
				}else{
					if(j.getPiece()->getKing()){
						boxTop = " W ";
					}else{
						boxTop = " w ";
					}
				}
			}else{
				boxTop = "   ";
			}

			// Add box comp onto topRow and bottomRow strings
			topRow = topRow + boxTop + '|';
			bottomRow = bottomRow + "___" + '|';
		}
		// Render full row
		cout << "   " << topRow << "\n";
		cout << " " << i+1 << " " << bottomRow << "\n";
	}
}

// TEMP - DO NOT DISTRIBUTE
void Game::testState(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			cout << i << j << " " << board[i][j].getColour() << endl;
		}
	}
	cout << "<------------>" << endl;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(board[i][j].getPiece() != NULL){
				cout << i << j << " " << board[i][j].getPiece()->getColour() << endl;
			}
		}
	}
}