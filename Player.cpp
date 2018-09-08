//player.cpp
#include "AIPlayer.h"
#include "player.h"
#include "board.h"
#include "game.h"
#include <iostream>
using namespace std;

Player::Player() {

}

bool Player::play(Board& board1) {
	board1.print();
	int space;
	if (isAI) {
		space = ai.move(board1);
		board1.change(space, symbol);
	}
	else {
		cout << symbol << ": ";
		cin >> space;
		--space;
		while (!board1.change(space, symbol)) {
			cout << "Invalid" << endl;
			board1.print();
			cout << symbol << ": ";
			cin >> space;
			--space;
		}
	}
	if (board1.isWin(space)) {
		return true;
	}
	return false;
}

char Player::getChar() {
	return symbol;
}

void Player::setChar(char c) {
	symbol = c;
}

void Player::setAI(bool b) {
	isAI = b;
}
