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

void drawBoard(vector< vector<int> > board)
{
	// Rendering the game grid
	
	cout << "    A   B   C   D   E   F   G   H \n\n";
	// Standard loop with accumulator for rendering rows
	for(int i = 0; i < 8; i++){
		string boxTop;
		string topRow;
		string bottomRow;
		
		for(auto &j : board[i]){
			boxTop = " " + to_string(j) + " ";

			// Add box comp onto topRow and bottomRow strings
			topRow = topRow + boxTop + '|';
			bottomRow = bottomRow + "___" + '|';

		}
		// Render full row
		cout << "   " << topRow << "\n";
		cout << " " << i+1 << " " << bottomRow << "\n";
	}

}

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

	drawBoard(board);
	
}