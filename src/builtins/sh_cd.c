#include "shell.h"

static int	sh_cd_opt(char *opt, char *str)
{
	if (!str || *str != '-' || (str[0] == '-' && (str[1] == '\0' ||
	((str[1] == ' ' || str[1] == '-') && (str[2] == '\0' || str[2] == ' ')))))
		return (0);
	if ((str[1] == 'L' || str[1] == 'P') && (str[2] == '\0' || str[2] == ' '))
	{
		*opt = str[1];
		return (1);
	}
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": cd: -", 2);
	ft_putchar_fd(str[1], 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("cd: usage: cd [-L|-P] [directory]\n"
			"           cd -", 2);
	return (-1);
}

int			sh_cd(char *av[])
{
	char	opt;
	char	*dir;
	int		i;

	i = 0;
	opt = 'L';
	if (!av[1] && sh_access(NULL, 0))
		return (1);
	if ((i = sh_cd_opt(&opt, av[1])) < 0)
		return (1);
	if (!(dir = ft_strdup(getenv("HOME"))) && !av[i + 1])
		return (ft_error("cd", "HOME not set", NULL));
	else if (av[i + 1])
	{
		free(dir);
		if (!(dir = ft_strdup(av[i + 1])))
			return (-1);
	}
	if (sh_cd2(dir, opt, av[i + 1]) < 0)
		return (-1);
	return (0);
}
