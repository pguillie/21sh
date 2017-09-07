#include "shell.h"

char	sh_conv_hex(char *str)
{
	char	c;
	size_t	i;

	c = 0;
	i = 0;
	while (i < 2 && ((str[i] >= '0' && str[i] <= '9')
			|| (str[i] >= 'A' && str[i] <= 'F')
			|| (str[i] >= 'a' && str[i] <= 'f')))
	{
		c = c * 16 + (str[i] > '9' ? str[i] - 'a' + 10 : str[i] - '0');
		i++;
	}
	return (c);
}
