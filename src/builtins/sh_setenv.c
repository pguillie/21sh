#include "shell.h"

static int	sh_set_env(char *var)
{
	extern char	**environ;
	int			i[2];

	i[1] = 0;
	if (!(var = ft_strdup(var)))
		return (-1);
	while (var[i[1]] && var[i[1]] != '=')
		i[1]++;
	i[0] = 0;
	if (environ)
	{
		while (environ[i[0]] && !(ft_strnequ(environ[i[0]], var, i[1])
					&& environ[i[0]][i[1]] == '='))
			i[0]++;
		if (environ[i[0]])
			free(environ[i[0]]);
		else if (!(environ = (char **)ft_realloc(environ,
						i[0] + 1, i[0] + 2, sizeof(char *))))
			return (-1);
	}
	else if (!(environ = (char **)ft_memalloc(sizeof(char *) * 2)))
		return (-1);
	environ[i[0]] = var;
	return (0);
}

int			sh_setenv_var(char *prg, char *var)
{
	int	j;

	j = 0;
	while (var[j] && var[j] != '=')
	{
		if (!((var[j] >= 'a' && var[j] <= 'z')
					|| (var[j] >= 'A' && var[j] <= 'Z')
					|| (var[j] >= '0' && var[j] <= '9')
					|| var[j] == '_'))
			break ;
		j++;
	}
	if (var[j] == '=')
		return (sh_set_env(var));
	else
		return (ft_error(prg, var, !var[j] ? E_EQMISS : E_ALNUM));
}

int			sh_setenv(char *av[])
{
	int	i;
	int	ret;
	int	stat;

	i = 1;
	stat = 0;
	while (av[i] && (ret = sh_setenv_var(av[0], av[i++])) >= 0)
		if (ret)
			stat = 1;
	if (ret == 0 && ft_strequ(av[0], "setenv") && ft_strnequ(av[1], "PATH", 4))
		sh_hash_free();
	return (ret < 0 ? ret : stat);
}
