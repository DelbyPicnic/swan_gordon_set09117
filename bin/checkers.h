// (C)2017 Gordon Swan (DELBYPICNIC)
// SET09117 Edinburgh Napier University
// Checkers

// INFORMATION
// 0 == BLACK == TOP
// 1 == WHITE == BOTTOM

#ifndef CHECKERS_H
#define CHECKERS_H
#endif
#include <string>
#include <vector>

using namespace std;

// Type for storing the xy coordin
typedef struct point
{
    int x;
    int y; 

} point;

bool operator == (const point &p1, const point &p2);
bool operator < (const point &p1, const int val);
bool operator > (const point &p1, const int val);
point operator + (const point &p1, const int val);
point operator + (const point &p1, const point &p2);
point operator * (const point &p1, const int val);

class Piece{
	private:
		int colour;
		bool isKing;
		bool isCaptured;
		point location;

	public:
		// TODO: add get/set methods
		int getColour(){return colour;};
		bool getKing(){return isKing;};
		bool getCaptured(){return isCaptured;};
		point getLocation(){return location;};

		void setLocation(point loc){location = loc;};

		Piece(int, point);
		void mkKing();
		void mkCapture();
};

class Position{
	private:
		Piece* piece;
		int colour;
	public:
		int getColour(){return colour;};
		Piece* getPiece(){return piece;};
		void setColour(int);
		void setPiece(Piece*);
};

class Move{
	private:
		string direction;
		int distance;
		point location;
		point dest;
		int value;
		Piece* piece;
		Piece* capture;

	public:
		string getDirection(){return direction;};
		int getDistance(){return distance;};
		point getDestination(){return dest;};
		point getLocation(){return location;};
		int getValue(){return value;};
		Piece* getPiece(){return piece;}
		Piece* getCapture(){return capture;};

		Move(Piece*, point, point);
		Move(Piece*, Piece*, point, point);
};

class Game{
	private:
		vector< vector<Position> > board;
		vector<Move*> m_history;
		int state_index;
		bool isWinner;
		int gameMode;   // What game ode is selected?
		int p_turn = 0;	// Whos turn is it?
		bool use_ai = false; // Should the AI be used to determine this move?
		
	public:
		bool usingAI(){return use_ai;};

		Game();
		void initGame();
		bool chkForWinner();
		void chkForKing();
		vector<Move*> getMoves();
		point getUsrInput();
		void playMove(Move*);
		void drawState();
		void rewindState();
		void redoState();
		void autoPlay();
		void autoSelect();
};

int evaluateMove(Move*);