#include "shell.h"

static int	sh_exec_hash(char *av[], char *env[])
{
	char	*path;
	int		ret;

	path = sh_hash_get(av[0]);
	if (path)
	{
		free(av[0]);
		if (!(av[0] = ft_strdup(path)))
			return (-1);
	}
	ret = sh_cmd_exec(av, env, &path);
	if (!ft_strchr(av[0], '/'))
		sh_hash_set(av[0], path);
	path ? free(path) : 0;
	return (ret);
}

int			sh_execution(char *av[], char *env[], int ret)
{
	if (ft_strequ(av[0], "echo"))
		return (sh_echo(av));
	else if (ft_strequ(av[0], "cd"))
		return (sh_cd(av));
	else if (ft_strequ(av[0], "setenv"))
		return (sh_setenv(av));
	else if (ft_strequ(av[0], "unsetenv"))
		return (sh_unsetenv(av));
	else if (ft_strequ(av[0], "env"))
		return (sh_env(av, env));
	else if (ft_strequ(av[0], "printenv"))
		return (sh_printenv(env, av[1]));
	else if (ft_strequ(av[0], "hash"))
		return (sh_hash(av));
	else if (ft_strequ(av[0], "exit"))
		return (sh_exit(av, ret));
	else
		return (sh_exec_hash(av, env));
}
