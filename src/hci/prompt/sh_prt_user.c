#include "shell.h"

int		sh_prt_user(char buff[], int *b)
{
	struct passwd	*p;
	int				i;

	i = 0;
	if ((p = getpwuid(getuid())))
	{
		while (p->pw_name[i])
		{
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = p->pw_name[i++];
		}
	}
	return (i);
}
