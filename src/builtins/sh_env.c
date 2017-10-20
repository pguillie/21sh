#include "shell.h"

int		sh_env(char *av[], char *env[])
{
	(void)env;
	if (!av[1])
		sh_printenv();
	return (0);
}
