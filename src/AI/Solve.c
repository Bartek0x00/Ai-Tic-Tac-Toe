#include <limits.h>
#include <stdio.h>
#include "Board.h"
#include "Color.h"

#define TO_SIGNED(x) (((x) == 1) ? -1 : 1)

static int negamax(Board board, Color color)
{
	int eval = Board_GetWinner(board);
	if (eval != 0)
		return TO_SIGNED(eval) * TO_SIGNED(color);
	
	int bestScore = INT_MIN;
	for (int i = 0; i < 9; i++) {
		if (!Board_Get(board, i)) {
			int score = -negamax(
				Board_Set(board, i, color),
				(color ^ 0b11)
			);

			if (score > bestScore)
				bestScore = score;
		}
	}
	return bestScore;
}

Board solve(Board board, Color color)
{
	int bestScore = INT_MIN;
	int bestMove = -1;

	for (int i = 0; i < 9; i++) {
		if (!Board_Get(board, i)) {
			int score = -negamax(
				Board_Set(board, i, color),
				(color ^ 0b11)
			);

			if (score > bestScore) {
				bestScore = score;
				bestMove = i;
			} 
		}
	}
	printf("bestMove: %u\n", bestMove);
	return Board_Set(board, bestMove, color);
}