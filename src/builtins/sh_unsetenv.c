#include "shell.h"

static int	sh_remove_var(char *var)
{
	extern char **environ;
	char		**new;
	int			i;
	int			j;

	i = 0;
	while (environ[i])
		i++;
	if (!(new = (char **)ft_memalloc(sizeof(char *) * i)))
		return (-1);
	i = 0;
	j = 0;
	while (environ[i])
	{
		if (!ft_strequ(environ[i], var))
			new[j++] = environ[i];
		i++;
	}
	if (ft_strnequ(var, "PATH", 4))
		sh_hash_free();
	free(environ);
	free(var);
	environ = new;
	return (0);
}

int			sh_unsetenv(char *av[])
{
	extern char	**environ;
	int			i;
	int			j;
	int			n;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (environ[j])
		{
			n = 0;
			while (av[i][n] == environ[j][n])
				n++;
			if (!av[i][n] && environ[j][n] == '=')
			{
				if (sh_remove_var(environ[j]) < 0)
					return (-1);
				break ;
			}
			j++;
		}
		i++;
	}
	return (0);
}
