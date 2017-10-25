#include "shell.h"

static int	sh_epur2(int *i, char **dir)
{
	char	*d;

	d = *dir;
	i[1] = i[0] > 0 ? i[0] - 1 : 0;
	while (i[1] && d[i[1]] != '/')
		i[1]--;
	if (sh_verif(d, i) < 0)
		return (-1);
	if (i[0])
		ft_memmove(d + i[1] + 1, d + i[0] + 2, i[0] - (i[1] + 1));
	else
		ft_memmove(d, d + 1, ft_strlen(d + 2));
	i[0] = i[1];
	*dir = d;
	return (0);
}

static int	sh_epur(char **curdir)
{
	int		i[2];
	char	*d;

	d = *curdir;
	i[0] = 0;
	while (d[i[0]])
	{
		if (ft_strnequ(d + i[0], "/./", 3) || ft_strequ(d + i[0], "/."))
			ft_memmove(d + i[0] + 1, d + i[0] + 2, ft_strlen(d + i[0] + 1));
		else if (ft_strnequ(d + i[0], "//", 2))
			ft_memmove(d + i[0], d + i[0] + 1, ft_strlen(d + i[0]));
		else if (ft_strnequ(d + i[0], "/../", 4) || ft_strequ(d + i[0], "/.."))
		{
			if (sh_epur2(i, &d) < 0)
				return (-1);
		}
		else if (ft_strequ(d + i[0], "/") && i[0])
			d[i[0]] = '\0';
		else
			i[0]++;
	}
	*curdir = d;
	return (1);
}

static int	sh_cd_exec(char opt, char *dir)
{
	char		*tab[3];
	int			ret;

	tab[2] = NULL;
	if ((ret = ft_access(dir, 0)) == 1 || chdir(dir) < 0)
		return (!ret ? -1 : 1);
	tab[0] = "setenv";
	if (!(tab[1] = ft_strjoin("OLDPWD=", getenv("PWD"))))
		return (-1);
	sh_setenv(tab);
	free(tab[1]);
	if (opt == 'P')
		dir = getcwd(dir, 32);
	if (!(tab[1] = ft_strjoin("PWD=", dir)))
		return (-1);
	sh_setenv(tab);
	free(tab[1]);
	return (0);
}

static int	sh_cd2(char *dir, char opt)
{
	if (getenv("CDPATH") && dir[0] != '.' && dir[0] != '/'
					&& sh_search_path(&dir) < 0)
		return (-1);
	if (opt != 'P' && dir[0] != '/' && sh_concat_pwd(&dir) < 0)
		return (-1);
	if (opt != 'P' && sh_epur(&dir) < 0)
		return (1);
	if (sh_cd_exec(opt, dir) < 0)
		return (-1);
	free(dir);
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
		if (!(dir = ft_strdup(getenv("OLDPWD"))))
			return (ft_error("cd", "OLDPWD not set", NULL));
	}
	if (sh_cd2(dir, opt) < 0)
		return (-1);
	return (0);
}
