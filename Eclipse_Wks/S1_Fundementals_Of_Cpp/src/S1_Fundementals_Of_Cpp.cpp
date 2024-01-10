//============================================================================
// Name        : S1_Fundementals_Of_Cpp.cpp
// Author      : Ezz Al-Qurtubi
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

//Return by reference feature in cpp
int& accumlate (int x, int y) {
	static int accumlator = 0;
	accumlator += x + y;
	return accumlator;
}

int main() {
	int &x = accumlate(1,2);		// x is now 3
	cout << x << endl;
	x++;							// x is now 4
	cout << x << endl;

	int &y = accumlate(0,1);		// x is now 5
	cout << x << endl;
	y++;							// x is now 6
	cout << x << endl;
	return 0;
}
