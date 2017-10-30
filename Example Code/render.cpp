// (C)2017 Gordon Swan (DELBYPICNIC)
// SET09117 Edinburgh Napier University
// Checkers

// This is to develop and test the render function

// INFORMATION
// 0 == BLACK == TOP
// 1 == WHITE == BOTTOM

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argv, char* argc[])
{	
	vector< vector<int> > board(8, vector<int>(8));

	// Fill array with test data (checkerboard data)
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(i % 2 == 0){
				if(j % 2 == 0){
					// 0
					board[i][j] = 0;
				}else{
					// 1
					board[i][j] = 1;
				}
			}else{
				if(j % 2 == 0){
					// 1
					board[i][j] = 1;
				}else{
					// 0
					board[i][j] = 0;
				}
			}	
		}
	}

	// Rendering the game grid
	string boxTop ("   ");
	string boxBottom ("___");

	for(auto &i : board){
		string topRow;
		string bottomRow;
		
		for(auto &j : board[0]){
			// Add box comp onto topRow and bottomRow strings
			topRow = topRow + boxTop + '|';
			bottomRow = bottomRow + boxBottom + '|';
		}
		// Render full row
		cout << topRow << "\n";
		cout << bottomRow << "\n";
	}

}