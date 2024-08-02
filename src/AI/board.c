#include "board.h"

#define N NONE //0b00
#define R RED  //0b01
#define B BLUE //0b10

#define BOARD(i0, i1, i2, i3, i4, i5, i6, i7, i8) \
	(Board)\
   (((i0) << 16) | \
	((i1) << 14) | \
	((i2) << 12) | \
	((i3) << 10) | \
	((i4) << 8) | \
	((i5) << 6) | \
	((i6) << 4) | \
	((i7) << 2) | \
	((i8) << 0))

const Board BOARD_WIN_RED[8] = { 
	BOARD( 
		R, R, R, 
		N, N, N, 
		N, N, N  
	), 
	BOARD( 
		N, N, N, 
		R, R, R, 
		N, N, N  
	), 
	BOARD( 
		N, N, N, 
		N, N, N, 
		R, R, R  
	), 
	BOARD( 
		R, N, N, 
		R, N, N, 
		R, N, N  
	), 
	BOARD( 
		N, R, N, 
		N, R, N, 
		N, R, N  
	), 
	BOARD( 
		N, N, R, 
		N, N, R, 
		N, N, R  
	), 
	BOARD(
		N, N, R,
		N, R, N,
		R, N, N
	),
	BOARD(
		R, N, N,
		N, R, N,
		N, N, R
	)
};

const Board BOARD_WIN_BLUE[8] = {
	BOARD(
		B, B, B,
		N, N, N,
		N, N, N
	),
	BOARD(
		N, N, N,
		B, B, B,
		N, N, N
	),
	BOARD(
		N, N, N,
		N, N, N,
		B, B, B
	),
	BOARD(
		B, N, N,
		B, N, N,
		B, N, N
	),
	BOARD(
		N, B, N,
		N, B, N,
		N, B, N
	),
	BOARD(
		N, N, B,
		N, N, B,
		N, N, B
	),
	BOARD(
		N, N, B,
		N, B, N,
		B, N, N
	),
	BOARD(
		B, N, N,
		N, B, N,
		N, N, B
	)
};

Color board_get_winner(Board board)
{
	for (int i = 0; i < 8; i++) {
		if ((board & BOARD_WIN_RED[i]) == BOARD_WIN_RED[i])
			return RED;
		if ((board & BOARD_WIN_BLUE[i]) == BOARD_WIN_BLUE[i])
			return BLUE;
	}
	return NONE;
}
