#ifndef _BOARD_H
#define _BOARD_H

#include "color.h"

typedef unsigned int Board;

#define BOARD_EMPTY (Board)0

extern const Board BOARD_WIN_RED[8];
extern const Board BOARD_WIN_BLUE[8];

extern Color board_get_winner(Board board);

#define BOARD_GET_WINNER(board) board_get_winner(board)

#define BOARD_GET(board, index) ((board >> (index * 2)) & 0b11)

#define BOARD_SET(board, index, color) \
	(Board)(((board) & ~(0b11 << ((index) * 2))) | \
			((color) << ((index) * 2)))


//Indexes of a Board:
//0 1 2
//3 4 5
//6 7 8

#endif //_BOARD_H
