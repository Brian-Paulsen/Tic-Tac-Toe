//player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"
#include "AIPlayer.h"
using namespace std;

class Player {
private:
	AIPlayer ai;
	char symbol;
	bool isAI = false;
public:
	Player();
	void setChar(char);
	char getChar();
	void setAI(bool);
	bool play(Board&);
};

#endif