#include "shell.h"

int		sh_cd_opt(char *opt, char *str)
{
	if (!str || *str != '-' || (str[0] == '-' && (str[1] == '\0' ||
	((str[1] == ' ' || str[1] == '-') && (str[2] == '\0' || str[2] == ' ')))))
		return (0);
	if ((str[1] == 'L' || str[1] == 'P') && (str[2] == '\0' || str[2] == ' '))
	{
		*opt = str[1];
		return (1);
	}
	ft_putstr_fd("21sh: cd: -", 2);
	ft_putchar_fd(str[1], 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
	return (-1);
}

int		sh_concat_pwd(char **dir)
{
	char		*tmp;
	char		*pwd;
	int			i;

	if (!(pwd = ft_strdup(getenv("PWD"))))
		pwd = getcwd(pwd, PATH_MAX);
	tmp = ft_strdup(*dir);
	free(*dir);
	i = 0;
	while (pwd[i])
		i++;
	if (ft_strequ(pwd, "/") && (ft_strequ(tmp, "..") || ft_strequ(tmp, "../")))
		*dir = ft_strdup("/");
	else if (pwd[i - 1] == '/')
		*dir = ft_strjoin(pwd, tmp);
	else
		*dir = ft_strcjoin(pwd, tmp, '/');
	free(tmp);
	free(pwd);
	return (*dir ? 0 : -1);
}

int		ft_access(char *dir, int mode, char *av)
{
	DIR		*fd;
	char	*str;

	str = NULL;
	if (ft_strequ(av, "-"))
		str = dir ? ft_strrchr(dir, '/') + 1 : NULL;
	else
		str = av;
	if (!dir || access(dir, F_OK) < 0)
	{
		return (!mode ? ft_error("cd", E_NOENT, str) : 1);
	}
	if (access(dir, X_OK) < 0)
		return (!mode ? ft_error("cd", E_NORGHT, str) + 1 : 2);
	if (!(fd = opendir(dir)))
		return (!mode ? ft_error("cd", E_NODIR, str) : 1);
	closedir(fd);
	return (0);
}

int		sh_search_path(char **dir, char *av)
{
	char		**cdpath;
	char		*tmp;
	int			i;

	i = 0;
	tmp = NULL;
	cdpath = ft_strsplit(getenv("CDPATH"), ':');
	while (cdpath[i])
	{
		tmp ? free(tmp) : 0;
		tmp = ft_strcjoin(cdpath[i], *dir, '/');
		if (ft_access(tmp, 1, av) != 1)
			break ;
		i++;
	}
	if (!cdpath[i])
	{
		tmp ? free(tmp) : 0;
		tmp = ft_strcjoin(".", *dir, '/');
	}
	free(*dir);
	*dir = tmp;
	ft_strtabdel(cdpath);
	return (0);
}
