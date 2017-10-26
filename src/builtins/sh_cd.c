#include "shell.h"

static void	sh_epur2(char **dir, int *i)
{
	char	*d;

	d = ft_strdup(*dir);
	while (d[i[0]])
	{
		if (ft_strnequ(d + i[0], "/./", 3) || ft_strequ(d + i[0], "/."))
			ft_memmove(d + i[0] + 1, d + i[0] + 2, ft_strlen(d + i[0] + 1));
		else if (ft_strnequ(d + i[0], "/../", 4) || ft_strequ(d + i[0], "/.."))
		{
			i[1] = i[0] > 0 ? i[0] - 1 : 0;
			while (i[1] && d[i[1]] != '/')
				i[1]--;
			ft_memmove(d + (i[1] ? i[1] : 1), d + i[0] + 3,
					ft_strlen(d + (i[1] ? i[1] : 1)) - (i[0] - i[1] - 2));
			i[0] = i[1];
		}
		else if (ft_strnequ(d + i[0], "//", 2))
			ft_memmove(d + i[0] + 1, d + i[0] + 2, ft_strlen(d + i[0] + 1));
		else if (ft_strequ(d + i[0], "/") && i[0])
			d[i[0]] = '\0';
		else
			i[0]++;
	}
	free(*dir);
	*dir = d;
}

static int	sh_epur(char **curdir, char *av)
{
	int		i[2];
	char	*d;

	d = ft_strdup(*curdir);
	i[0] = 0;
	if (ft_access(d, 1, av) != 0 && !ft_strequ(av, av[1] && av[2] ? "../" : ".."))
	{
		free(d);
		return (1);
	}
	av ? sh_epur2(&d, i) : 0;
	ft_printf("d:%s\n", d);
	if (av && ft_strequ(av, av[1] && av[2] ? "../" : "..") &&
		(i[0] = ft_access(d, 1, av)) != 0)
	{
		free(d);
		return (i[0] == 2 ? 1 : 2);
	}
	else
	{
		free(*curdir);
		*curdir = d;
	}
	return (1);
}

static int	sh_cd_exec(char opt, char *dir, int epu, char *av)
{
	char		*tab[3];
	char		*path;
	int			ret;

	ret = 0;
	tab[2] = NULL;
	if (epu != 2 && ft_access(dir, 0, av) != 0)
		return (1);
	tab[0] = "setenv";
	if (!(tab[1] = ft_strjoin("OLDPWD=", getenv("PWD"))))
		return (-1);
	sh_setenv(tab);
	free(tab[1]);
	path = ft_strdup(dir);
	if (opt == 'P')
	{
		if (ft_access(path, 1, av) == 0)
			ret = chdir(path);
		free(dir);
		dir = getcwd(NULL, PATH_MAX);
	}
	if (!(tab[1] = ft_strjoin("PWD=", dir)))
	{
		free(path);
		free(dir);
		return (-1);
	}
	sh_setenv(tab);
	free(tab[1]);
	if (opt != 'P' && ft_access(path, 1, av) == 0)
		ret = chdir(path);
	free(path);
	free(dir);
	return (ret < 0 ? -1 : 0);
}

static int	sh_cd2(char *dir, char opt, char *av)
{
	int ret;

	ret = 0;
	if (getenv("CDPATH") && dir[0] != '.' && dir[0] != '/'
			&& sh_search_path(&dir, av) < 0)
		return (-1);
	(void)opt;
	if (opt != 'P' && dir[0] != '/' && sh_concat_pwd(&dir) < 0)
		return (-1);
	if (opt != 'P' && (ret = sh_epur(&dir, av)) < 0)
		return (1);
	if ((ret = sh_cd_exec(opt, dir, ret, av)) < 0)
		return (-1);
	ret == 1 ? free(dir) : 0;
	return (0);
}

int			sh_cd(char *av[])
{
	char		opt;
	char		*dir;
	int			i;

	i = 0;
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
	if (ft_strequ(dir, "-"))
	{
		free(dir);
		if (!(dir = ft_strdup(getenv("OLDPWD"))) || ft_strequ(dir, ""))
		{
			if (dir && ft_strequ(dir, ""))
				free(dir);
			return (ft_error("cd", "OLDPWD not set", NULL));
		}
	}
	if (sh_cd2(dir, opt, av[i + 1]) < 0)
		return (-1);
	return (0);
}
