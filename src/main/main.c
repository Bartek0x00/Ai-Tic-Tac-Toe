#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif //__EMSCRIPTEN__

#define ATOI(num) ((num) - '0')

static unsigned int remaining_moves = 9;
static Color player_color = 0;

static Board algorithm(Board board)
{
	while (1) {
		Color winner = BOARD_GET_WINNER(board);
		if (winner) {
			// Well, if someone won, it is not the player
			show_text("You've lost\n", RED);
			remaining_moves = 0;
			draw_display(board);
			return board;
		}

		if (!remaining_moves) {
			show_text("It's a tie\n", BLUE);	
			draw_display(board);
			return board;
		}

	#ifdef __EMSCRIPTEN__
		emscripten_sleep(16);
		board = solve(board, COLOR_SWAP(player_color));
		show_text("Solve time: < 1ms\n", NONE);
		draw_display(board);
		emscripten_sleep(1);

	#else //__EMSCRIPTEN__
		struct timespec start_time, end_time;
		clock_gettime(CLOCK_MONOTONIC, &start_time);

		board = solve(board, COLOR_SWAP(player_color));
		
		clock_gettime(CLOCK_MONOTONIC, &end_time);
		long elapsed_time = (end_time.tv_nsec - start_time.tv_nsec);
	
		char buff[32] = {'\0'};
	
		snprintf(buff, sizeof(buff), "Solve time: %ldns\n", elapsed_time);
		show_text(buff, NONE);
		draw_display(board);
	#endif //__EMSCRIPTEN__
	
		// If there are remaining_moves left and 
		// there is no winner, give a turn to the player
		if (--remaining_moves)
			if (!BOARD_GET_WINNER(board)) 
				return board;
	}
}

static Board user(Board board)
{
	while (1) {
		unsigned char input = '\0';

		while(!get_event(&input)) {
		#ifdef __EMSCRIPTEN__
			emscripten_sleep(1);
		#endif //__EMSCRIPTEN__
		}

		if (input == 'q') {
			delete_display();
			exit(EXIT_SUCCESS);
		}
		
		if (!remaining_moves)
			continue;

		if (!BOARD_GET(board, ATOI(input))) {
			board = BOARD_SET(board, ATOI(input), player_color);
			draw_display(board);
			remaining_moves--;
			return board;
		}
	}
}

int main(void)
{
	register Board board = BOARD_EMPTY;

	init_display(); 

	srand(time(0));
	player_color = (rand() % 2) + 1;
	
	if (player_color == RED) {
		show_text("You're red cross X\n", RED);
		draw_display(BOARD_EMPTY);
		board = user(board);
	}

	while (1) {
		board = algorithm(board);
		board = user(board);
	}
	return 0;	
}
