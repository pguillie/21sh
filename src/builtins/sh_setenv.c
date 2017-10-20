#include "shell.h"

int		sh_setenv_var(char *var)
{
	extern char	**environ;
	int			i;
	int			n;

	i = 0;
	n = 0;
	while (var[n] && var[n] != '=')
		n++;
	while (environ[i] && !ft_strnequ(environ[i], var, n))
		i++;
	if (!environ[i])
	{
		if (!(environ = ft_realloc(environ, i, i + 1, sizeof(char *))))
			return (-1);
	}
	environ[i] = var;
	return (0);
}



int		sh_setenv(char *av[])
{
	int	i;
	int	j;
	int	ret;
	extern char	**environ;

	i = 0;
	while (av[++i])
	{
		j = 0;
		while (av[i][j] && av[i][j] != '=')
		{
			if (!((av[i][j] >= 'a' && av[i][j] <= 'z') ||
					(av[i][j] >= 'A' && av[i][j] <= 'Z') || av[i][j] == '_')
					|| (av[i][j] >= '0' && av[i][j] <= '9'))
				break ;
			j++;
		}
		if (av[i][j] == '=')
		{
			if ((ret = sh_setenv_var(ft_strdup(av[i])) < 0))
				return (ret);
			ft_printf("%d\n", __LINE__);
			ft_strtab_disp(environ);
			ft_printf("%d\n", __LINE__);
		}
		else
			ft_error("setenv", av[i], !av[i][j] ? E_EQMISS : E_ALNUM);
	}
	return (ret);
}
