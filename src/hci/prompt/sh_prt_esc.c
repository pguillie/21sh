#include "shell.h"

int		sh_prt_esc(char buff[], int *b, char *ps)
{
	int		i;

	i = 1;
	if (*b == PRT_SIZE)
		*b = ft_flush_buff(buff, PRT_SIZE);
	buff[(*b)++] = 27;
	if (*b == PRT_SIZE)
		*b = ft_flush_buff(buff, PRT_SIZE);
	buff[*b] = ps[i++];
	if (buff[(*b)++] == '[')
	{
		while (ps[i] < '@' || ps[i] > '~')
		{
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = ps[i++];
		}
		if (*b == PRT_SIZE)
			*b = ft_flush_buff(buff, PRT_SIZE);
		buff[(*b)++] = ps[i++];
	}
	return (i);
}
