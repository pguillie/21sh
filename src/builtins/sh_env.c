#include "shell.h"

static int	sh_env_error(char c)
{
	ft_printf("env: illegal option -- %c\n", c);
	ft_putendl("usage: env [-i] [name=value]... [utility [argument...]]");
	return (1);
}

static int	sh_env_opt(char *opt)
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

static int	sh_env_set(char *av[], int *i)
{
	char	*back[2];
	int		j;
	int		ret;

	j = *i;
	while (av[*i] && ft_strchr(av[*i], '='))
		*i += 1;
	back[0] = av[j - 1];
	back[1] = av[*i];
	if (!(av[j - 1] = ft_strdup("env")))
		return (-1);
	av[*i] = NULL;
	ret = sh_setenv(av + j - 1);
	free(av[j - 1]);
	av[j - 1] = back[0];
	av[*i] = back[1];
	return (ret);
}

static int	sh_env_end(char *av[], int i, char *env[])
{
	if (!av[i])
		return (sh_printenv(env, NULL));
	return (sh_execution(av + i, env, 0));
}

int			sh_env(char *av[], char *env[])
{
	extern char	**environ;
	char		**bac_env;
	int			ignore;
	int			i;
	int			ret;

	if (!av[1])
		return (sh_printenv(env, NULL));
	bac_env = environ;
	environ = sh_envdup(env);
	i = 1;
	if ((ignore = sh_env_opt(av[i])) < 0)
		return (sh_env_error(av[i][-ignore]));
	else if (ignore && ++i)
	{
		environ ? ft_strtabdel(environ) : 0;
		environ = NULL;
	}
	ret = sh_env_set(av, &i);
	env = environ;
	environ = bac_env;
	if (ret >= 0)
		ret = sh_env_end(av, i, env);
	env ? ft_strtabdel(env) : 0;
	return (ret);
}
