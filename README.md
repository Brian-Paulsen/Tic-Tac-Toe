# TIC-TAC-TOE
This project creates a tic-tac-toe game with an AI player. The AI randomly picks based on the rules written below. I
originally hacked together this project during my freshmen year, so the code quality is less than great.

## AI Rules
The AI makes its decisions according to the following:
```
1. If there are one of more moves where the AI is guaranteed to win, it will pick one of those moves 
with each move having an equal probability of being chosen.

2. Otherwise, it will look at all the possible moves that don't give the player a winning strategy, 
and randomly pick one based cubed probability of winning given player assumptions described below.
```
There are board states where the every possible move the AI makes gives the player a winning strategy, but those board states aren't accounted for. If
the rules described above are followed, it is impossible for one of those board states to come up.

## Player Assumptions
The only way that a player should be able to win tic-tac-toe is if at least one of the players, doesn't play optimally; therefore, it wouldn't
be helpful for the AI to assume that players play optimally. Instead, the AI assumes the player is going to make their move based on the following
criteria:
```
1. If the AI can win next turn (i.e. there are two symbols in an empty space the same direction), 
then the player will block it.

2. Otherwise, the player will pick a random move.
```
This doesn't make any assumption about how the player will play if they have the opportunity to win because if the AI is implemented corrected,
that situation should never happen.
