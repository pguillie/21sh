#include "shell.h"

int		sh_printenv(void)
{
	extern char **environ;
	int			i;

	i = 0;
	while (environ[i])
		ft_putendl(environ[i++]);
	return (0);
}
