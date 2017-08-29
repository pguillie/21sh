#include "shell.h"

char	sh_conv_oct(char *str)
{
	char	c;
	size_t	i;

	c = 0;
	i = 0;
	while (i < 2 && (str[i] >= '0' && str[i] < '8'))
		c = c * 8 + str[i++] - '0';
	return (c);
}
