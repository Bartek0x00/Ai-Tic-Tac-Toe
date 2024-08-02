#include <limits.h>
#include <stdio.h>
#include "board.h"
#include "color.h"

#define TO_SIGNED(x) (((x) == 1) ? -1 : 1) 

static int is_draw(Board board)
{
	for (int i = 0; i < 9; i++) 
		if (!BOARD_GET(board, i))
			return 0;
	return 1;
}

static int negamax(Board board, Color color, int alpha, int beta)
{
	int eval = BOARD_GET_WINNER(board);
	
	if (eval != 0)
		return TO_SIGNED(eval) * TO_SIGNED(color);
	
	if (is_draw(board)) 
		return 0;

	int best_score = -2;
	for (int i = 0; i < 9; i++) {
		if (!BOARD_GET(board, i)) {
			int score = -negamax(
				BOARD_SET(board, i, color),
				COLOR_SWAP(color),
				-beta,
				-alpha
			);

			if (score > best_score)
				best_score = score;

			if (best_score > alpha)
				alpha = best_score;

			if (alpha >= beta)
				break;
		}
	}
	return best_score;
}

Board solve(Board board, Color color)
{
	int best_score = -2;
	int best_move = -1;
	int alpha = -2;
	int beta = 2;

	for (int i = 0; i < 9; i++) {
		if (!BOARD_GET(board, i)) {
			int score = -negamax(
				BOARD_SET(board, i, color),
				COLOR_SWAP(color),
				-beta,
				-alpha
			);

			if (score > best_score) {
				best_score = score;
				best_move = i;
				
				if (best_score > alpha)
					alpha = best_score;

				if (alpha >= beta)
					break;
			} 
		}
	}
	return BOARD_SET(board, best_move, color);
}
