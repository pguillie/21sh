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
	ft_putstr_fd(SHELL, 2);
	ft_putstr_fd(": cd: -", 2);
	ft_putchar_fd(str[1], 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("cd: usage: cd [-L|-P] [directory]\n"
			"           cd -", 2);
	return (-1);
}

int		sh_concat_pwd(char **dir)
{
	char		*tmp;
	char		*pwd;
	int			i;

	if (!(pwd = ft_strdup(getenv("PWD"))))
		pwd = getcwd(pwd, PATH_SIZE);
	if (!(tmp = ft_strdup(*dir)))
		return (-1);
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
		return (!mode ? ft_error("cd", E_NOENT, str) : 1);
	if (!(fd = opendir(dir)))
		return (!mode ? ft_error("cd", E_NODIR, str) : 1);
	closedir(fd);
	if (access(dir, X_OK) < 0)
		return (!mode ? ft_error("cd", E_NORGHT, str) + 1 : 2);
	return (0);
}

int		sh_search_path(char **dir, char *av, int i)
{
	char	**cdpath;
	char	*tmp;

	tmp = NULL;
	if (!(cdpath = ft_strsplit(getenv("CDPATH"), ':')))
		return (-1);
	while (cdpath[i])
	{
		tmp ? free(tmp) : 0;
		if (!(tmp = ft_strcjoin(cdpath[i], *dir, '/')))
			return (-1);
		if (ft_access(tmp, 1, av) != 1)
			break ;
		i++;
	}
	if (!cdpath[i])
	{
		tmp ? free(tmp) : 0;
		if (!(tmp = ft_strcjoin(".", *dir, '/')))
			return (-1);
	}
	free(*dir);
	*dir = tmp;
	ft_strtabdel(cdpath);
	return (0);
}

int		sh_cd_exec2(char opt, char **dir, char **tab, char *av)
{
	int ret;

	ret = 0;
	if (opt == 'P')
	{
		if (ft_access(tab[0], 1, av) == 0)
			ret = chdir(tab[0]);
		free(*dir);
		*dir = getcwd(NULL, PATH_SIZE);
	}
	if (!(tab[2] = ft_strjoin("PWD=", *dir)))
	{
		free(tab[0]);
		free(*dir);
		return (-1);
	}
	return (ret);
}
