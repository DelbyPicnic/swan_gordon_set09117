#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void)
{
	vector<int> stack;
	stack.push_back(0);
	stack.push_back(1);
	stack.push_back(2);
	stack.push_back(3);

	for(auto &i : stack){
		cout << i << " ";
	}
	cout << endl;
}