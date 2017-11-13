#include "shell.h"

static void	sh_epur2(char **d, int *i)
{
	while ((*d)[i[0]])
	{
		if (ft_strnequ(*d + i[0], "/./", 3) || ft_strequ(*d + i[0], "/."))
			ft_memmove(*d + i[0] + 1, *d + i[0] + 2, ft_strlen(*d + i[0] + 1));
		else if (ft_strnequ(*d + i[0], "/../", 4)
				|| ft_strequ(*d + i[0], "/.."))
		{
			i[1] = i[0] > 0 ? i[0] - 1 : 0;
			while (i[1] && (*d)[i[1]] != '/')
				i[1]--;
			ft_memmove(*d + (i[1] ? i[1] : 1), *d + i[0] + 3,
					ft_strlen(*d + i[0] + 2));
			i[0] = i[1];
		}
		else if (ft_strnequ(*d + i[0], "//", 2))
			ft_memmove(*d + i[0] + 1, *d + i[0] + 2, ft_strlen(*d + i[0] + 1));
		else if (ft_strequ(*d + i[0], "/") && i[0])
			(*d)[i[0]] = '\0';
		else
			i[0]++;
	}
}

static int	sh_epur(char **curdir, char *av)
{
	int		i[2];
	char	*d;

	if (!(d = ft_strdup(*curdir)))
		return (-1);
	i[0] = 0;
	if (ft_access(d, 1, av) != 0 &&
			!ft_strequ(av, av[1] && av[2] ? "../" : ".."))
	{
		free(d);
		return (1);
	}
	av ? sh_epur2(&d, i) : 0;
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
	char		*tab[4];
	int			ret;

	ret = 0;
	tab[3] = NULL;
	tab[1] = "setenv";
	if (epu != 2 && ft_access(dir, 0, av) != 0)
		return (1);
	if (!(tab[2] = ft_strjoin("OLDPWD=", getenv("PWD"))))
		return (-1);
	sh_setenv(tab + 1);
	free(tab[2]);
	if (!(tab[0] = ft_strdup(dir)))
		return (-1);
	if ((ret = sh_cd_exec2(opt, &dir, tab, av)) < 0)
		return (-1);
	sh_setenv(tab + 1);
	free(tab[2]);
	if (opt != 'P' && ft_access(tab[0], 1, av) == 0)
		ret = chdir(tab[0]);
	free(tab[0]);
	free(dir);
	return (ret < 0 ? -1 : 0);
}

static int	sh_cd2(char *dir, char opt, char *av)
{
	int i[2];

	ft_bzero(i, sizeof(int) * 2);
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
	if (getenv("CDPATH") && dir[0] != '.' && dir[0] != '/'
			&& sh_search_path(&dir, av, i[1]) < 0)
		return (-1);
	if (opt != 'P' && dir[0] != '/' && sh_concat_pwd(&dir) < 0)
		return (-1);
	if (opt != 'P' && (i[0] = sh_epur(&dir, av)) < 0)
		return (1);
	if ((i[0] = sh_cd_exec(opt, dir, i[0], av)) < 0)
		return (-1);
	i[0] == 1 ? free(dir) : 0;
	return (0);
}

int			sh_cd(char *av[])
{
	char		opt;
	char		*dir;
	int			i;

	i = 0;
	opt = 'L';
	if (!av[1] && access(getenv("HOME"), F_OK))
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
