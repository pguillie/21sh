#include "shell.h"

int		sh_exit(char *av[], int ret)
{
	if (av && av[1])
	{
		if (av[2])
			return (ft_error(av[0], E_2MNARG, NULL));
		ret = ft_atoi(av[1]);
	}
	ft_putendl("exit");
	exit(ret);
}
