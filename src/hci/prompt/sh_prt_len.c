#include "shell.h"

int		sh_prt_len(char buff[])
{
	size_t	i;
	int		len;

	i = 0;
	len = 0;
	while (buff[i])
	{
		if (buff[i] == '\n' || buff[i] == '\r')
			len = 0;
		else
			len += 1;
		i++;
	}
	return (len);
}
