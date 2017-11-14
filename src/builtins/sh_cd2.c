#include "shell.h"

static int	sh_search_path(char **dir, int i)
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
		if (sh_access(tmp, 1) != 1)
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

static int	sh_concat_pwd(char **dir)
{
	char	*tmp;
	char	*pwd;
	int		i;

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
	if (sh_access(d, 1) != 0 &&
			!ft_strequ(av, av[1] && av[2] ? "../" : ".."))
	{
		free(d);
		return (1);
	}
	av ? sh_epur2(&d, i) : 0;
	if (av && ft_strequ(av, av[1] && av[2] ? "../" : "..") &&
			(i[0] = sh_access(d, 1)) != 0)
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

int			sh_cd2(char *dir, char opt, char *av)
{
	int	i[2];

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
			&& sh_search_path(&dir, i[1]) < 0)
		return (-1);
	if (opt != 'P' && dir[0] != '/' && sh_concat_pwd(&dir) < 0)
		return (-1);
	if (opt != 'P' && (i[0] = sh_epur(&dir, av)) < 0)
		return (i[0]);
	if ((i[0] = sh_cd_exec(opt, dir, i[0])) < 0)
		return (-1);
	i[0] == 1 ? free(dir) : 0;
	return (i[0]);
}
