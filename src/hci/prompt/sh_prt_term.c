#include "shell.h"

int		sh_prt_term(char buff[], int *b)
{
	char	*term;
	int		i;
	int		n;
	int		len;

	len = 0;
	if ((term = ttyname(0)))
	{
		i = 0;
		n = 0;
		while (term[i])
			if (term[i++] == '/')
				n = i;
		while (term[n])
		{
			len = (term[n] == '\n' ? 0 : len + 1);
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = term[n++];
		}
	}
	return (len);
}
