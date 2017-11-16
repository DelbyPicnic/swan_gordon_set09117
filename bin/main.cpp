// (C)2017 Gordon Swan (DELBYPICNIC)
// SET09117 Edinburgh Napier University
// Checkers

// INFORMATION
// 0 == BLACK == TOP
// 1 == WHITE == BOTTOM

#include <iostream>
#include <vector>
#include <string>
#include "checkers.h"
#include <exception>

using namespace std;

int main(int argv, char* argc[])
{	
	while(true){
		Game* m_game = new Game();
		m_game->initGame();
		bool m_active = true;

		while(m_active){
			vector<Move*> allMoves = m_game->getMoves();
			bool m_input = false;

			m_game->drawState();

			while(!m_input){
				cout << "\nActions:\n[1] Select Piece\n[2] Undo Last Action\n[3] Redo Last Action\n[4] Use AI to Select Move\n[5] Play All States \n[6] Exit to Main Menu" << endl;
				string usrInp;
				getline(cin,usrInp);

				try{
					if(stoi(usrInp, nullptr, 10) == 1){
						cout << "\nEnter the coords for the piece you want to move:" << endl;
						point p_loc = m_game->getUsrInput();
						cout << "Enter the coords for the space you're moving it to:" << endl;
						point p_dest = m_game->getUsrInput();

						bool move_found = false;
						Move* sel_move;

						for(auto &m : allMoves){
							if(p_loc == m->getLocation() && p_dest == m->getDestination()){
								if(m->getDirection() == "FORWARD" || m->getPiece()->getKing() == true){
									move_found = true;
									sel_move = m;
								}else{
									cout << "Only king pieces can move backwards" << endl; 
								}
							}
						}


						if(move_found){
							m_game->playMove(sel_move);
						}else{
							cout << "Selected move isn't valid. Please try again!" << endl;
						}

						m_input = true;

					}else{

						switch(stoi(usrInp, nullptr, 10)){
							case 2: cout << "<---\n" << endl;
									m_game->rewindState();
									m_input = true;
									break;
							case 3: cout << "--->\n" << endl;
									m_game->redoState();
									m_input = true;
									break;
							case 4: cout << "...asking Siri" << endl;
									m_game->autoSelect();
									m_input = true;
									break;
							case 5: cout << "...playing all moves" << endl;
									m_game->autoPlay();
									m_input = true;
									break;
							case 6: cout << "Quitting..." << endl;
									m_input = true;
									m_active = false;
						}
					}
				}catch(const exception &ex){
					cout << "Please enter a number.... (Argument Exception)\n" << endl;
					break;
				}
				m_game->chkForKing();
				if(m_game->chkForWinner()){
					cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
					cout << "!!!!!!!!!!!W I N R A R!!!!!!!!!!!" << endl;
					cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
				}
			}
		}
		m_game = NULL;
	}
}