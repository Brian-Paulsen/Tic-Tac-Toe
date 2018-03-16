//game.cpp
#include "board.h"
#include "game.h"
#include "player.h"
#include <iostream>
using namespace std;

Game::Game() {

	char input;
	cout << "first? (y or n): ";
	cin >> input;
	input = toupper(input);
	players[0].setChar('X');
	players[0].setAI(!(input == 'Y'));
	players[1].setChar('O');
	players[1].setAI(input == 'Y');
}

void Game::start() {

	bool tie = true;
	for (int i = 0; i < 9; ++i) {
		if (players[i % 2].play(board1)) {
			board1.print();
			cout << players[i % 2].getChar() << " Wins!" << endl;
			tie = false;
			break;
		}
	}
	if (tie) {
		board1.print();
		cout << "Tie!" << endl;
	}
}
