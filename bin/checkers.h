// (C)2017 Gordon Swan (DELBYPICNIC)
// SET09117 Edinburgh Napier University
// Checkers

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
} location;

class Piece{
	private:
		int colour;
		bool isKing;
		bool isCaptured;
		location loc;

	public:
		// TODO: add get/set methods
		Piece(int, location);
		void King();
		void Capture();
};

class Move{
	private:
		string direction;
		int distance;
		location dest;
		int value;
		Piece* piece;

	public:
		// TODO: add get/set methods
		Move(Piece*, location);
		void Play();
};