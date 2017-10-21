#include "shell.h"

int		sh_init_env(void)
{
	extern char	**environ;
	int			ret;

	if (!(environ = sh_envdup(environ)))
		return (-1);
	ret = 0;
	return (ret);
}
