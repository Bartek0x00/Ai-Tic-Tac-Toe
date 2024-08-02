#include <stdio.h>
#include <sys/ioctl.h>

int get_event(unsigned char *output)
{
	scanf("%c", output);
	ioctl(0, 0x540b, 0);
	
	if (*output == 'q') 
		return 1;
	
	if ((*output >= '0') && (*output <= '8')) 
		return 1;
	
	return 0;
}
