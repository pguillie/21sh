#include "shell.h"

int		sh_printenv(char *env[], char *var)
{
	char	*val;
	int		i;

	if (var)
	{
		if ((val = getenv(var)))
			ft_putendl(val);
		else
			return (1);
	}
	else if (env)
	{
		i = 0;
		while (env[i])
			ft_putendl(env[i++]);
	}
	return (0);
}
