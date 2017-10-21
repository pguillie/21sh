#include "shell.h"

int		sh_init_env(void)
{
	extern char	**environ;

	if (!(environ = sh_envdup(environ)))
		return (-1);
	return (1);
}
