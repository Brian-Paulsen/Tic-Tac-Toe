#include "AIPlayer.h"
#include "board.h"
#include <stack>
#include <queue>
#include <cmath>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


bool isWin(int* spots) {
	for (int i = 0; i < 9; i += 3) {
		if (spots[i] == spots[i + 1] && spots[i] == spots[i + 2] && spots[i] != 0) {
			return true;
		}
	}
	for (int i = 0; i < 3; i++) {
		if (spots[i] == spots[i + 3] && spots[i] == spots[i + 6] && spots[i] != 0) {
			return true;
		}
	}
	if (spots[0] == spots[4] && spots[0] == spots[8] && spots[0] != 0) {
		return true;
	}
	if (spots[2] == spots[4] && spots[2] == spots[6] && spots[2] != 0) {
		return true;
	}
	return false;
}


AIPlayer::AIPlayer() {
	boardStates = new node[19683];
	this->makeGraph();
}

int AIPlayer::makeRand() {
	int num = rand();
	num = (num << 16) + rand();
	return num;
}


void process(node * pnode, queue<node*> &nodes, AIPlayer * player) {

	//set spots array to match board
	int temp = pnode->index;
	pnode->spots = new int[9];
	for (int i = 8; i >= 0; i--) {
		int p = int(pow(3, i) + 0.5);
		pnode->spots[i] = temp / p;
		temp %= p;
	}

	//check if someone won
	if (isWin(pnode->spots)) {
		pnode->isWin = true;
		return;
	}
	pnode->isWin = false;

	//set up next layer
	int e = pnode->layer % 2; //is 1 for o and 0 for x
	pnode->next = new node*[9 - pnode->layer];
	int count = 0;
	for (int i = 0; i < 9; i++) {
		if (pnode->spots[i] == 0) {
			int j = pnode->index + int(pow(3, i)*(e + 1) + 0.5);//next node
			node* tnode = &(player->boardStates)[j];
			tnode->index = j;
			pnode->next[count++] = tnode;
			if (!tnode->inQueue) {
				tnode->layer = pnode->layer + 1;
				nodes.push(tnode);
				tnode->inQueue = true;
			}
		}
	}
}


void calcprob(node* cnode, int size) {

	if (size % 2 == 1) {//if it is x's move
						//calcualate xoporan
		int top = 0;
		int bottom = 0;
		int max = 0;
		int owin = 0;
		cnode->xwinst = false;
		cnode->owinst = false;
		for (int i = 0; i < size; ++i) {
			node* tnode = cnode->next[i];
			if (!tnode->nextWin) {//if o does not win next turn
				top += tnode->oopxran;
				bottom++;
			}
			if (tnode->xoporan > max) {
				max = tnode->xoporan;
			}
			if (tnode->xwinst) {
				cnode->xwinst = true;
			}
			if (tnode->owinst) {
				owin++;
			}
		}
		cnode->xoporan = max;
		if (owin == size) {
			cnode->owinst = true;
		}
		if (bottom == 0) {
			cnode->oopxran = 50000;
		}
		else {
			cnode->oopxran = top / bottom;
		}
	}

	else {//if it is o's move
		int top = 0;
		int bottom = 0;
		int max = 0;
		int xwin = 0;
		cnode->xwinst = false;
		cnode->owinst = false;
		for (int i = 0; i < size; i++) {
			node* tnode = cnode->next[i];
			if (!tnode->nextWin) {
				top += tnode->xoporan;
				bottom += 1;
			}
			if (tnode->oopxran > max) {
				max = tnode->oopxran;
			}
			if (tnode->xwinst) {
				xwin++;
			}
			if (tnode->owinst) {
				cnode->owinst = true;
			}
		}
		cnode->oopxran = max;
		if (xwin == size) {
			cnode->xwinst = true;
		}
		if (bottom == 0) {
			cnode->xoporan = 50000;
		}
		else {
			cnode->xoporan = top / bottom;
		}
	}
}


void calculate(node* cnode, AIPlayer* player) {

	//base case
	if (cnode->isWin) {
		cnode->xoporan = cnode->layer % 2 ? 50000 : 0;
		cnode->oopxran = cnode->layer % 2 ? 0 : 50000;
		cnode->xwinst = cnode->layer % 2 ? true : false;
		cnode->owinst = cnode->layer % 2 ? false : true;
		return;
	}
	if (cnode->layer == 9) {
		cnode->xoporan = 0;
		cnode->oopxran = 0;
		cnode->xwinst = false;
		cnode->owinst = false;
		return;
	}
	//check nextWin
	cnode->nextWin = false;
	for (int i = 0; i < 9 - cnode->layer; i++) {
		if (cnode->next[i]->isWin) {
			cnode->nextWin = true;
		}
	}

	//calculates oranxop and xranoop
	calcprob(cnode, 9 - cnode->layer);
}


void AIPlayer::makeGraph() {
	queue<node*> frontier;
	stack<node*> nodeStack;
	boardStates[0].layer = 0;
	boardStates[0].index = 0;
	frontier.push(&boardStates[0]);

	while (!frontier.empty()) {
		node* tnode = frontier.front();
		frontier.pop();
		process(tnode, frontier, this);
		nodeStack.push(tnode);
	}

	while (!nodeStack.empty()) {
		node* tnode = nodeStack.top();
		nodeStack.pop();
		calculate(tnode, this);
	}
}


int AIPlayer::move(Board board1) {
	
	//use summation to find board state index
	int sum = 0;
	for (int i = 0; i < 9; i++) {
		if (board1.getMoves()[i] == 'X') {
			sum += int(pow(3, i) + 0.5);
		}
		else if (board1.getMoves()[i] == 'O') {
			sum += int(pow(3, i) + 0.5) * 2;
		}
	}


	node* currState = &(this->boardStates[sum]);

	if (currState->layer % 2 == 1) { //if it's o's turn
		int* nextStates = new int[9 - currState->layer];
		int goodMoves = 0;
		for (int i = 0; i < 9 - currState->layer; i++) {
			if (currState->next[i]->owinst) {
				nextStates[i] = 1;
				goodMoves++;
			}
			else {
				nextStates[i] = 0;
			}
		}
		if (goodMoves) { //if x has winning strategy
			int i = makeRand() % goodMoves;
			int j = 0;
			int k = 0;
			while (k <= i) {
				if (nextStates[j] == 1) {
					k++;
				}
				j++;
			}
			j--;
			int boxChosen = currState->next[j]->index - currState->index;
			delete[] nextStates;

			return int(log(boxChosen) / log(3)); //return
		}
		goodMoves = 0;
		for (int i = 0; i < 9 - currState->layer; i++) {
			if (!currState->next[i]->xwinst) {
				nextStates[i] = int(pow(currState->next[i]->oopxran + 1, 2) / 15000 + 1);
				goodMoves += nextStates[i];
			}
		}
		int i = makeRand() % goodMoves + 1;
		int j = 0;
		while (i > 0) {
			i -= nextStates[j];
			++j;
		}
		j--;
		int l = currState->next[j]->index - currState->index;
		delete[] nextStates;
		return int(log(l) / log(3));
	}

	else {//if it's x's turn

		int* nextStates = new int[9 - currState->layer];
		int goodMoves = 0;
		for (int i = 0; i < 9 - currState->layer; i++) {
			if (currState->next[i]->xwinst) {
				nextStates[i] = 1;
				goodMoves++;
			}
			else {
				nextStates[i] = 0;
			}
		}
		if (goodMoves) {
			int i = makeRand() % goodMoves;
			int j = 0;
			int k = 0;
			while (k <= i) {
				if (nextStates[j] == 1) {
					k++;
				}
				j++;
			}
			j--;
			int boxChosen = currState->next[j]->index - currState->index;
			delete[] nextStates;
			return int(log(boxChosen) / log(3) + 0.5);
		}
		int weightTotal = 0;
		for (int i = 0; i < 9 - currState->layer; i++) {
			if (!currState->next[i]->owinst) {
				
				//calculation for move weight
				nextStates[i] = int(pow(currState->next[i]->xoporan + 1, 2) / 15000 + 1); 

				weightTotal += nextStates[i];
			}
		}
		int i = makeRand() % weightTotal + 1;
		int j = 0;
		while (i > 0) {
			i -= nextStates[j];
			++j;
		}
		j--;
		int l = currState->next[j]->index - currState->index;
		delete[] nextStates;
		return int(log(l) / log(3) + 0.5);
	}
}