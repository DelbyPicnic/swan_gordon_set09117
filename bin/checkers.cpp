// (C)2017 Gordon Swan (DELBYPICNIC)
// SET09117 Edinburgh Napier University
// Checkers

// INFORMATION
// 0 == BLACK == TOP
// 1 == WHITE == BOTTOM

#include "checkers.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <locale>

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

Move::Move(Piece* p, point l, point d)
{
	piece = p;
	location = l;
	dest = d;

	// Distance must be calculated
	int dx = abs(location.x - dest.x);
	int dy = abs(location.y - dest.y);
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

	// Request a value for this move from the AI
	value = 1; // TEMP
		// Move evaluation will be bolted on at a later stage, 
		// there will be a call to an AI API here once i've written it.
		// Evaluation will run from 1 to 5, with 1 being the worst and 5
		// being the best.
}

Move::Move(Piece* p, Piece* c, point l, point d)
{
	piece = p;
	capture = c;
	location = l;
	dest = d;

	// Distance must be calculated
	int dx = abs(location.x - dest.x);
	int dy = abs(location.y - dest.y);
	if(dx == dy){
		if(dx < 3 && dx > 2){
			distance = dx;
		}else{
			throw invalid_argument("Move displacement is incorrect for the type of move");
		}
	}else{
		throw invalid_argument("Movement is not diagonal");
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

	// Request a value for this move from the AI
	value = 2; // TEMP
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
vector<Move*> Game::getMoves()
{
	vector<Move*> moves;

	// Declare all offsets, this could be neater...
	point a; a.x = -1; a.y = -1;
	point b; b.x = -1; b.y = 1;
	point c; c.x = 1; c.y = -1;
	point d; d.x = 1; d.y = 1;
	// Add points to iteratable
	point offset [] = {a, b, c, d};

	for(int i = 0; i < 8; i++){
		for(auto &j : board[i]){
			if(j.getPiece() != NULL){
				if(j.getPiece()->getColour() == p_turn){
					Piece* p = j.getPiece();
					point loc = p->getLocation();

					for(auto &off : offset){
						point offs_loc;
						offs_loc.x = (loc.x + off.x);
						offs_loc.y = (loc.y + off.y); 

 						if(offs_loc.x > 7 || offs_loc.x < 0 || offs_loc.y > 7 || offs_loc.y < 0){
 							continue;
 						}

						if(board[offs_loc.y][offs_loc.x].getPiece() == NULL){
							//regular move is available
							Move* regMove = new Move(p, loc, offs_loc);
							moves.push_back(regMove);

						}else if(board[loc.y + off.y][loc.x + off.x].getPiece()->getColour() != p_turn && board[loc.y + (off.y*2)][loc.x + (off.x*2)].getPiece() == NULL){
							//jump move is availabe
							// Get piece to capture
							Piece* c = board[loc.y + off.y][loc.x + off.x].getPiece();
							// Get double offset point
							point jmp_offs;
							jmp_offs.x = loc.x + (off.x*2);
							jmp_offs.y = loc.y + (off.y*2);

							Move* jmpMove = new Move(p, c, loc, jmp_offs);
							moves.push_back(jmpMove);
						}
					}
				}
			}
		}
	}
	
	/*
	// TEMP
	for(auto &m : moves){
		cout << m->getLocation().x << "," << m->getLocation().y << " to " << m->getDestination().x << "," << m->getDestination().y << endl;
	}
	*/
	
	return moves;
}
point Game::getUsrInput(){
	bool isValid = false;
	string usrIn;
	string cols = "abcdefgh";
	point p_pos;

	while(!isValid){
		getline(cin, usrIn);
		if(usrIn.size() == 2){
			if(isalpha(usrIn[0])){
				char xVal = tolower(usrIn[0], locale());
				auto xpos = cols.find(xVal);
				if(xpos != string::npos){
					p_pos.x = xpos;
				}else{
					cout << "Column not found or is out of range." << endl;
				}
			}else{
				cout << "Column value is invalid." << endl;
			}
			if(isdigit(usrIn[1])){
				int val = usrIn[1] - '0';
				val--;
				if(val < 0 || val > 7){
					cout << "Row value is out of range." << endl;
				}else{
					p_pos.y = val;
				}
			}else{
				cout << "Row value is invalid." << endl;
			}
		}else{
			cout << "Input shoud be exactly two characters long." << endl;
		}
		
		if(p_pos.x <= 7 && p_pos.x >= 0){
			if(p_pos.x <= 7 && p_pos.x >= 0){
				isValid = true;
			}
		}
	}
	return p_pos;
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

Move* Game::getNextMove()
{
	string usrInp;	
	if(gameMode == 1){
		if(p_turn == 0){
			cout << "Black Turn - Player 1" << endl;
			point p_cur = this->getUsrInput();
			
		}else{
			cout << "White Turn - Player 2" << endl;
		}
	}else if(gameMode == 2){
		if(p_turn == 0){
			cout << "Black Turn - Computer" << endl;
		}else{
			cout << "White Turn - Player 1" << endl;
		}
	}else if(gameMode == 3){
		if(p_turn == 0){
			cout << "Black Turn - Computer" << endl;
		}else{
			cout << "White Turn - Computer" << endl;
		}
	}
	
}

void Game::playMove(Move* m)
{
	point curPos = m->getLocation();
	point newPos = m->getDestination();

	if(board[newPos.y][newPos.x].getPiece() == NULL){
		board[newPos.y][newPos.x].setPiece(board[curPos.y][curPos.x].getPiece());
		board[newPos.y][newPos.x].getPiece()->setLocation(m->getDestination());
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