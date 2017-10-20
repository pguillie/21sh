#include "shell.h"

int		sh_echo(char *av[])
{
	size_t	i;

	i = 1;
	while (av[i])
	{
		ft_putstr(av[i++]);
		if (av[i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return (0);
}
