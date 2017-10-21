#include "shell.h"

int		sh_prt_uid(char buff[], int *b)
{
	if (*b == PRT_SIZE)
		*b = ft_flush_buff(buff, PRT_SIZE);
	buff[(*b)++] = (geteuid() ? '$' : '#');
	return (1);
}
