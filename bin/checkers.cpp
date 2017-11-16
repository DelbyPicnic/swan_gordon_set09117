// (C)2017 Gordon Swan (DELBYPICNIC)
// SET09117 Edinburgh Napier University
// Checkers

// INFORMATION
// 0 == BLACK == TOP
// 1 == WHITE == BOTTOM

#include "checkers.h"
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <locale>

using namespace std;

// Define comparitor functionality between points and other types.
bool operator == (const point &p1, const point &p2)
{
	if(p1.x == p2.x && p1.y == p2.y){
		return true;
	}else{
		return false;
	}
}
bool operator < (const point &p1, const int val)
{
	if(p1.x < val || p1.y < val){
		return true;
	}else{
		return false;
	}
}
bool operator > (const point &p1, const int val)
{
	if(p1.x > val || p1.y > val){
		return true;
	}else{
		return false;
	}
}
point operator + (const point &p1, const int val)
{
	point nPoint;
	nPoint.x = p1.x + val;
	nPoint.y = p1.y + val;
	return nPoint;
}
point operator + (const point &p1, const point &p2)
{
	point nPoint;
	nPoint.x = p1.x + p2.x;
	nPoint.y = p1.y + p2.y;
	return nPoint;
}
point operator * (const point &p1, const int val)
{
	point nPoint;
	nPoint.x = p1.x * val;
	nPoint.y = p1.y * val;
	return nPoint;
}

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
		if(dx > 0 && dx < 3){
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
						use_ai = true;
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

void Game::initGame()
{
	// Initialise the gamestate
	board.resize( 8, vector<Position>(8));
	p_turn = 0;
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
			if(foundBlack && foundWhite){
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

// Find all moves for all pieces of a particular side and return as a vector 
vector<Move*> Game::getMoves()
{
	vector<Move*> moves;

	// Declare all offsets
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
						point offs_loc = loc +off;

						if(offs_loc > 7 || offs_loc < 0){
 							continue;
 						}

 						if(board[offs_loc.y][offs_loc.x].getPiece() == NULL){
							Move* regMove = new Move(p, loc, offs_loc);
							if(regMove->getDirection() == "FORWARD" || regMove->getPiece()->getKing() == true){
								moves.push_back(regMove);
							}
						}else{
							if(board[offs_loc.y][offs_loc.x].getPiece()->getColour() != p_turn){
								point jmp_offs = loc + (off*2);

								if(jmp_offs > 7 || jmp_offs < 0){
									continue;
								}
								if(board[jmp_offs.y][jmp_offs.x].getPiece() == NULL){
									// Grab piece to capture
									Piece* cap = board[offs_loc.y][offs_loc.x].getPiece();
									// Create new move
									Move* jmpMove = new Move(p, cap, loc, jmp_offs);
									if(jmpMove->getDirection() == "FORWARD" || jmpMove->getPiece()->getKing() == true){
										moves.push_back(jmpMove);
									}
								}
							}
						}
					}
				}
			}
		}
	}

	
	// Filter all moves for jump moves, if jump moves exist, only send the jump moves
	vector<Move*> j_moves;
	for(auto &m : moves){
		if(m->getDistance() == 2 && m->getCapture() != NULL){
			// Capture move is in the list
			j_moves.push_back(m);
		}
	}
	// If there's jump moves available return only those, else return regular moves
	if(j_moves.size() > 0){
		cout << "There is a capture move available!" << endl;
		return j_moves;
	}else{
		return moves;
	}
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

void Game::playMove(Move* m)
{
	point curPos = m->getLocation();
	point newPos = m->getDestination();

	if(board[newPos.y][newPos.x].getPiece() == NULL){
		board[newPos.y][newPos.x].setPiece(board[curPos.y][curPos.x].getPiece());
		board[newPos.y][newPos.x].getPiece()->setLocation(m->getDestination());
		board[curPos.y][curPos.x].setPiece(NULL);

		if(m->getCapture() != NULL && m->getDistance() == 2){
			point capPos = m->getCapture()->getLocation();
			board[capPos.y][capPos.x].setPiece(NULL);
			// captured a piece
		}
		m_history.push_back(m);
		state_index++;

		// If state index does not match move history, after playing a new move, shrink the move history
		// This prevents the player from beig able to set an old - possibly invalid - state.
		if(state_index != m_history.size()){
			m_history.resize(state_index);
			cout << "Move History has been clipped as new move has been played." << endl;
		}

		// Select next player
		if(p_turn == 0){
			p_turn = 1;
		}else{
			p_turn = 0;
		}
		if(gameMode == 2){
			if(use_ai == false){
				use_ai = true;
			}else{
				use_ai = false;
			}
		}

	}else{
		cout << newPos.x << "," << newPos.y << " is occupied" << endl;
		throw invalid_argument("Invalid move detected: Destination is occupied");
	}
	
	// If this move was a jump move, check for another available jump move
	if(m->getDistance() == 2 && m->getCapture() != NULL){
		// Get list of moves, filter for jump moves relating to the current piece
		vector<Move*> nxt_mv_lst = this->getMoves();
		for(auto &nxt_m : nxt_mv_lst){
			if(nxt_m->getDistance() == 2 && nxt_m->getCapture() != NULL){
				if(nxt_m->getPiece() == m->getPiece()){
					this->playMove(nxt_m);
					break;
				}
			}
		}
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
	// Display whos turn it is
	if(p_turn == 0){
		cout << "Black Turn";
	}else{
		cout << "White Turn";
	}
	// Display who is playing (computer/user) && Get input from correct source
	if(use_ai){
		cout << " - Computer" << endl;
		// Get input from AI
	}else{
		cout << " - Player" <<endl;
	}
}

void Game::rewindState()
{
	// Check if there's a previous state to rewind to
	if(state_index > 0){
		// If so, get previous move information.
		Move* m = m_history[state_index-1];
		point newPos = m->getLocation();
		point curPos = m->getDestination();
		int pSide = m->getPiece()->getColour();

		// Create new instance of the piece that is to be added
		Piece* p = new Piece(pSide, newPos);

		// Reinstate board from history
		board[newPos.y][newPos.x].setPiece(p);
		board[curPos.y][curPos.x].setPiece(NULL);
		cout << "Successfully reinstated board history" << endl;

		// If last move was a capture piece then reinstate the piece in it's location prior to the move.
		if(m->getCapture() != NULL){
			// Remove captured piece if necessary.
			point capPos = m->getCapture()->getLocation();
			board[capPos.y][capPos.x].setPiece(m->getCapture());
		}

		// Finally, reinstate the player turn information.
		if(p_turn == 0){
			p_turn = 1;
		}else{
			p_turn = 0;
		}
		if(gameMode == 2){
			if(use_ai == false){
				use_ai = true;
			}else{
				use_ai = false;
			}
		}
		state_index--;

	}else{
		cout << "No actions to undo" << endl;
	}
}

void Game::redoState(){
	if(state_index < m_history.size()){

		Move* m = m_history[state_index];
		point newPos = m->getDestination();
		point curPos = m->getLocation();

		// Reinstate board from history
		board[newPos.y][newPos.x].setPiece(board[curPos.y][curPos.x].getPiece());
		board[newPos.y][newPos.x].getPiece()->setLocation(m->getDestination());
		board[curPos.y][curPos.x].setPiece(NULL);

		// If next move was a capture piece then remove piece from the board again.
		if(m->getCapture() != NULL){
			// Replace captured piece
			point capPos = m->getCapture()->getLocation();
			board[capPos.y][capPos.x].setPiece(NULL);
		}

		// Finally, reinstate the player turn information.
		if(p_turn == 0){
			p_turn = 1;
		}else{
			p_turn = 0;
		}
		if(gameMode == 2){
			if(use_ai == false){
				use_ai = true;
			}else{
				use_ai = false;
			}
		}
		state_index++;

	}else{
		cout << "No actions to redo" << endl;
	}
}

// Function to play all the saved moves 

void Game::autoPlay(){
	// Clear board state
	board.resize( 0, vector<Position>(0));
	p_turn = 0;
	this->initGame();
	this->drawState();
	cout << m_history.size() << endl;
	
	for(auto &m : m_history){
		point curPos = m->getLocation();
		point newPos = m->getDestination();
		
		if(board[newPos.y][newPos.x].getPiece() == NULL){
			board[newPos.y][newPos.x].setPiece(board[curPos.y][curPos.x].getPiece());
			board[newPos.y][newPos.x].getPiece()->setLocation(m->getDestination());
			board[curPos.y][curPos.x].setPiece(NULL);

			if(m->getCapture() != NULL && m->getDistance() == 2){
				point capPos = m->getCapture()->getLocation();
				board[capPos.y][capPos.x].setPiece(NULL);
				// captured a piece
			}

		}else{
			cout << newPos.x << "," << newPos.y << " is occupied" << endl;
			throw invalid_argument("Invalid move detected: Destination is occupied");
		}

		// Select next player
		if(p_turn == 0){
			p_turn = 1;
		}else{
			p_turn = 0;
		}
		if(gameMode == 2){
			if(use_ai == false){
				use_ai = true;
			}else{
				use_ai = false;
			}
		}
		this->drawState();
	}
}

// Function to automatically select a move on the layer's behalf
void Game::autoSelect(){
	vector<Move*> allMoves = this->getMoves();
	if(allMoves.size() > 0){
		int rndSel = rand() % allMoves.size();
		this->playMove(allMoves[rndSel]);
	}else{
		cout << "Couldn't select a move as there's no moves available" << endl;
	}
}