#include <iostream>
#include <string>
#include <locale>

using namespace std;

int main()
{
	string usrIn;
	string cols = "abcdefgh";

	getline(cin, usrIn);

	if(usrIn.size() == 2){
		cout << "...verified string size" << endl;
		if(isalpha(usrIn[0])){
			cout << "...verified first value is letter" << endl;
			char xVal = tolower(usrIn[0], locale());
			cout << "...converted to lowercase: " << xVal << endl;
			auto xPos = cols.find(xVal);
			if(xPos != string::npos){
				cout << xPos << endl;
			}else{
				cout << "Column value couldnt be found" << endl;
			}
		}
		if(isdigit(usrIn[1])){
			int val = usrIn[1] - '0';
			cout << val << endl;
		}
	}
}


/*
bool isValid = false;
	string cols = "abcdefgh";
	point p_pos;

	while(!isValid){
		try{
			if(usrIn.size() == 2){
				if(isalpha(usrIn[0])){
					string xVal = tolower(usrIn.substr(0,1), locale());
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
					int val = usrIn[1] -1;
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
		}catch(...){
			cout << "whatever" << endl;
			isValid = false;
			break;
		}
		isValid = true;
	}
	return p_pos;
*/