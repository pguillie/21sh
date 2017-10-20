#include "shell.h"

int		sh_env(char *av[], char *env[])
{
	if (!av[1])
		sh_printenv();
}
