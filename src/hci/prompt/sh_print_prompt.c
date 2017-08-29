#include "shell.h"

int		sh_print_prompt(char *ps)
{
	size_t	i;
	int		len;

	len = 0;
	i = 0;
	while (ps[i])
	{
		if (ps[i] == '\\')
		{
			len += sh_prompt_conv(ps + ++i);
			if (ps[i])
				i++;
		}
		else
		{
			ft_putchar(ps[i++]);
			len += 1;
		}
	}
	return (len);
}
