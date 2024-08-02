#include <stdio.h>
#include "../AI/color.h"

#define T_CLR "\033[0m"
#define T_RED "\033[38;5;1m"
#define T_BLUE "\033[38;5;4m"

void show_text(char *text, Color color)
{
	if (color == RED) 
		printf("\n%s%s%s", T_RED, text, T_CLR);
	
	else if (color == BLUE) 
		printf("\n%s%s%s", T_BLUE, text, T_CLR);
	
	else
		printf("\n%s", text);
}
