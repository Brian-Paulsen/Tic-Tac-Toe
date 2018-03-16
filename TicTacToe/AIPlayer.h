#ifndef AIP_H_
#define AIP_H_

#include "board.h"
#include <queue>
#include <stack>
using namespace std;

struct node {
	bool inQueue = false; //if it has been processed
	bool isWin; //is a winning board state
	node** next; //pointers to next possible board states
	int* spots; //board state
	int index; //index in array
	int layer; //number of symbols on board
	bool nextWin; //if opponent can win next turn
	bool xwinst; //if x has winning strategy
	bool owinst; //if o has winning strategy
	int xoporan; //probability times 50000 of x winning if o is random, and o plays optimally
	int oopxran; //probability times 50000 of o winning if x is random, and x plays optimally
};

class AIPlayer {
private:
	node * boardStates;
	friend void process(node*, queue<node*>&, AIPlayer*);
	friend void calculate(node*, AIPlayer*);
	void makeGraph();
	int makeRand();

public:
	AIPlayer();
	int move(Board);
};

#endif