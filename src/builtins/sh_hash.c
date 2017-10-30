#include "shell.h"

static int	sh_hash_error(char c)
{
	ft_printf("hash: -%c: invalid option\n", c);
	ft_putendl("usage: hash [utility...]");
	ft_putendl("       hash [-r]");
	return (1);
}

static int	sh_hash_opt(char *opt)
{
	int i;

	if (opt[0] != '-')
		return (0);
	i = 1;
	while (opt[i] && opt[i] == 'r')
		i++;
	if (opt[i] && opt[i] != 'r')
		return (-i);
	return (1);
}

int			sh_hash(char *av[])
{
	int		i;
	int		opt;
	char	*path;

	i = 1;
	path = NULL;
	if (!av[1])
		sh_hash_disp();
	else if ((opt = sh_hash_opt(av[i])) < 0)
		return (sh_hash_error(av[i][-opt]));
	else if (opt)
		sh_hash_free();
	while (av[i] && av[i][0] == '-')
		i++;
	while (av[i])
	{
		if (!ft_strchr(av[i], '/'))
			if (!sh_hash_get(av[i]) && !sh_exec_bin(av[i], &path))
				sh_hash_set(av[i], path);
		i++;
	}
	return (0);
}
