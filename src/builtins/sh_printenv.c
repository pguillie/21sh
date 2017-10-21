#include "shell.h"

//man:     printenv [name]

int		sh_printenv(char *env[])
{
	int			i;

	if (env)
	{
		i = 0;
		while (env[i])
			ft_putendl(env[i++]);
	}
	return (0);
}
