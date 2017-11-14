#include "shell.h"

int		sh_access(char *dir, int mode)
{
	if (!dir && !(dir = getenv("HOME")))
		return (!mode ? ft_error("cd", E_NOVAR("HOME"), NULL) + 1 : 2);
	if (access(dir, F_OK) < 0)
		return (!mode ? ft_error("cd", dir, E_NOENT) + 1 : 2);
	else if (access(dir, X_OK) < 0)
		return (!mode ? ft_error("cd", dir, E_NORGHT) + 1 : 2);
	return (0);
}
