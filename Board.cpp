//board.cpp
#include "board.h"
#include <iostream>
using namespace std;

Board::Board() {
	moves = new char[9];
	for (int i = 0; i < 9; ++i) {
		moves[i] = i + 49;
	}
}

void Board::print() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << (isdigit(moves[3 * i + j]) ? ' ' : moves[3 * i + j]);
			if (j < 2) {
				cout << '|';
			}
		}
		cout << "  ";
		for (int j = 0; j < 3; j++) {
			cout << i * 3 + j + 1;
			if (j < 2) {
				cout << '|';
			}
		}
		if (i < 2) {
			cout << endl << "-----  -----" << endl;
		}
	}
	cout << endl << endl;
}

bool Board::isWin(int spot) {
	char c = moves[spot];
	int rows = spot / 3;//index of the start of the row
	int cols = spot % 3;//index of the start of the col
	if (moves[3 * rows] == moves[3 * rows + 1] && moves[3 * rows] == moves[3 * rows + 2]) {//row check
		return true;
	}
	if (moves[cols] == moves[cols + 3] && moves[cols] == moves[cols + 6]) {//col check
		return true;
	}
	if (moves[0] == moves[4] && moves[0] == moves[8]) {//check l to r diagonal
		return true;
	}
	if (moves[2] == moves[4] && moves[2] == moves[6]) {//check r to l diagonal
		return true;
	}
	return false;
}

bool Board::change(int spot, char c) {
	if (!isdigit(moves[spot])) {
		return false;
	}
	moves[spot] = c;
	return true;
}

char* Board::getMoves() {
	return moves;
}