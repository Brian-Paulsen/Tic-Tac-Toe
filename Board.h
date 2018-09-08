//board.h
#ifndef BOARD_H_
#define BOARD_H_

using namespace std;

class Board {
private:
	char* moves;
public:
	Board();
	void print();
	bool isWin(int);
	bool change(int, char);
	char* getMoves();
};

#endif
