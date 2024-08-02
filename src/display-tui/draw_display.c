#include <stdio.h>
#include <stdlib.h>
#include "../AI/board.h"

static inline char get_char(Board board, int index)
{
	switch(BOARD_GET(board, index)) {
		case RED: 
			return 'X';
		case BLUE: 
			return 'O';
		default: 
			return ' ';
	}
}

void draw_display(Board board)
{
	printf(
		" %c | %c | %c \n"
		"---|---|---\n"
		" %c | %c | %c \n"
		"---|---|---\n"
		" %c | %c | %c \n",
		get_char(board, 0),
		get_char(board, 1),
		get_char(board, 2),
		get_char(board, 3),
		get_char(board, 4),
		get_char(board, 5),
		get_char(board, 6),
		get_char(board, 7),
		get_char(board, 8)
	);
}
