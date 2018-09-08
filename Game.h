//game.h
#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "player.h"
using namespace std;

class Game {
private:
	Board board1;
	Player players[2];
public:
	void start();
	Game();
};

#endif
