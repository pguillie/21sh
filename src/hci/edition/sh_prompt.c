#include "shell.h"

int		sh_prompt(int mode)
{
	int		len;

	len = -1;
	if (mode == 1)
	{
		ft_putstr("prompt $ ");
		len = 9;
	}
	else if (mode == 2)
	{
		ft_putstr("> ");
		len = 2;
	}
	return (len);
}
