//main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"
using namespace std;

int main() {
	srand(int(time(NULL)));
	bool play = true;
	char input;
	while (play) {
		Game game1;
		game1.start();
		cout << "Again? (y or n): ";
		cin >> input;
		if (tolower(input) != 'y') {
			play = false;
		}
	}
}