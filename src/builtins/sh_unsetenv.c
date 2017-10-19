#include "shell.h"

static int	sh_remove_var(char *var)
{
	extern char **environ;
	char		**tmp;
	int			i;

	i = 0;
	while (environ[i])
		i++;
	if (!(tmp = (char **)ft_memmalloc(sizeof(char*) * i)))
		return (-1);
	i = 0;
	while (environ[i])
	{
		if (!strequ(environ[i], var) && !(tmp[i] = ft_strdup(environ[i])))
		{
			ft_strtabdel(tmp);
			return (-1);
		}
		i++;
	}
	environ = tmp;
	return (0);
}

int			sh_unsetev(char *av[])
{
	extern char	*environ;
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
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
