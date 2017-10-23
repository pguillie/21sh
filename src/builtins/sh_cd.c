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
	ft_putstr_fd("21sh: cd: -", 2);
	ft_putchar_fd(str[1], 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putendl_fd("cd: usage: cd [-L|-P] [dir]", 2);
	return (-1);
}

static int	sh_concat_pwd(char **dir)
{
	char		*tmp;
	char		*pwd;
	int			i;

	tmp = *dir;
	free(*dir);
	pwd = getenv("PWD");
	i = 0;
	while (pwd[i])
		i++;
	*dir = ft_strcjoin(pwd, tmp, pwd[i - 1] == '/' ? 0 : '/');
	return (*dir ? 0 : -1);
}

static int	sh_epur(char **curdir)
{
	int		i;
	int		j;
	char	*dir;

	dir = *curdir;
	i = 0;
	while (dir[i])
	{
		if (((i && dir[i - 1] == '/') || i == 0) && dir[i] == '.' && dir[i + 1] == '/')
		{
			ft_memmove(dir + i, dir + i + 2, ft_strlen(dir + i));
			i = -1;
		}
		else if (((i && dir[i - 1] == '/') || i == 0) && dir[i] == '.' && dir[i + 1] == '.' && dir[i + 2] == '/')
		{
			j = i - 1;
			while (j - 1 && dir[j - 1] != '/')
				j--;
			ft_memmove(dir + j, dir + i + 3, ft_strlen(dir + j));
			i = -1;
		}
		i++;
	}
	*curdir = dir;
	return (1);
}

static int	sh_cd_exec(char *dir)
{
	extern char	**environ;
	char		*old;
	int			i;

	i = 0;
	if (access(dir, F_OK) < 0)
		return (ft_error("cd", E_NOENT, NULL));
	if (access(dir, X_OK) < 0)
		return (ft_error("cd", E_NORGHT, NULL));
	if (chdir(dir) < 0)
		return (-1);
	old = ft_strdup(getenv("PWD"));
	while (environ[i])
	{
		if (ft_strnequ(environ[i], "PWD=", 4))
		{
			free(environ[i]);
			if (!(environ[i] = ft_strjoin("PWD=", dir)))
				return (-1);
		}
		if (ft_strnequ(environ[i], "OLDPWD=", 7))
		{
			free(environ[i]);
			if (!(environ[i] = ft_strjoin("OLDPWD=", old)))
			{
				free(old);
				return (-1);
			}
			free(old);
		}
		i++;
	}
	return (0);
}

int		sh_cd(char *av[])
{
	char		opt;
	char		*dir;
//	char		*path;
	extern char	**environ;

	if (sh_cd_opt(&opt, av[1]) < 0)
		return (1);
	
	if (!(dir = ft_strdup(getenv("HOME"))) && !av[1])
		return (ft_error("cd", "HOME not set", NULL));
	else if (av[1])
	{
		free(dir);
		if (!(dir = ft_strdup(av[1])))
			return (-1);
	}
	if (ft_strequ(dir, "-"))
	{
		ft_printf("lol");
		free(dir);
		if (!(dir = ft_strdup(getenv("OLDPWD"))))
			return (ft_error("cd", "OLDPWD not set", NULL));
	}
	//step5
	if (getenv("CDPATH") && dir[0] != '.')
	{
//	if (sh_search_path(&path, dir) < 0)
//		return (-1);
//	else if (!path)
//		return (-1);
	//step6
//	free(dir);
//	dir = path;
	}
	//step7
	if (opt == 'P')
	{
		ft_putendl("step 7: opt: P: go to step 10");
		return (-1);
	}
	else if (dir[0] != '/' && sh_concat_pwd(&dir) < 0)
		return (-1);
	//step8
	ft_printf("dir:%s\n", dir);
	ft_putendl("step8 epur tous les ./ and epur ../ and epur multi /");
	if (sh_epur(&dir) < 0)
		return (-1);
	ft_printf("dir:%s\n", dir);
	//step10
	ft_putendl("execute and display error if any");
	if (sh_cd_exec(dir) < 0)
		return (-1);
	free(dir);
	return (0);
}
