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
typedef struct
{
    int x;
    int y; 
} point;


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
		point dest;
		int value;
		Piece* piece;

	public:
		string getDirection(){return direction;};
		int getDistance(){return distance;};
		point getDestination(){return dest;};
		int getValue(){return value;};
		Piece* getPiece(){return piece;}

		Move(Piece*, point);
		void Play();
};

class Game{
	private:
		vector< vector<Position> > board;
		bool isWinner;
	public:
		Game();
		bool chkForWinner();
		void chkForKing();
		void drawState();
		// getMoves, rewind, ff, end, save, load
};