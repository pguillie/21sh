#include "shell.h"

int		sh_printenv(char *env[])
{
	extern char **environ;
	int			i;

	if (env)
	{
		i = 0;
		while (environ[i])
			ft_putendl(environ[i++]);
	}
	return (0);
}
