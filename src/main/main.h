#ifndef _MAIN_H
#define _MAIN_H

#include "../AI/color.h"
#include "../AI/board.h"

extern void init_display(void);
extern int get_event(unsigned char *output);
extern void draw_display(Board board);
extern void delete_display(void);
extern void show_text(char *text, Color color);

extern Board solve(Board board, Color color);

#endif // _MAIN_H
