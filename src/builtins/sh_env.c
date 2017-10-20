#include "shell.h"

static int		sh_env_error(char c)
{
	ft_printf("env: illegal option -- %c\n", c);
	ft_putendl("usage: env [-i] [name=value]... [utility [argument...]]");
	return (1);
}

static int		sh_env_opt(char *opt)
{
	int		i;

	if (opt[0] != '-')
		return (0);
	i = 1;
	while (opt[i] && opt[i] == 'i')
		i++;
	if (opt[i] && opt[i] != 'i')
		return (-i);
	return (1);
}

int		sh_env(char *av[], char *env[])
{
	extern char	**environ;
	char		**bac_env;
	int			ignore;
	int			i;

	if (!av[1])
		return (sh_printenv(env));
	bac_env = environ;
	environ = env;
	i = 1;
	if ((ignore = sh_env_opt(av[i])) < 0)
		return (sh_env_error(av[i][-ignore]));
	else if (ignore)
	{
		ft_strtabdel(environ);
		environ = NULL;
		env = NULL;
		i++;
	}
	while (ft_strchr(av[i], '='))
		sh_setenv_var(av[i++]);//secu
	environ = bac_env;
	sh_execution(av + i, env);
	return (0);
}
