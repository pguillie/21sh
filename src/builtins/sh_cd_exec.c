#include "shell.h"

static int	sh_cd_exec2(char opt, char **dir, char **tab)
{
	int	ret;

	ret = 0;
	if (opt == 'P')
	{
		if (sh_access(tab[0], 1) == 0)
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

int			sh_cd_exec(char opt, char *dir, int epu)
{
	char	*tab[4];
	int		ret;

	ret = 0;
	tab[3] = NULL;
	tab[1] = "setenv";
	if (epu != 2 && sh_access(dir, 0) != 0)
		return (1);
	if (!(tab[2] = ft_strjoin("OLDPWD=", getenv("PWD"))))
		return (-1);
	sh_setenv(tab + 1);
	free(tab[2]);
	if (!(tab[0] = ft_strdup(dir)))
		return (-1);
	if ((ret = sh_cd_exec2(opt, &dir, tab)) < 0)
		return (-1);
	sh_setenv(tab + 1);
	free(tab[2]);
	if (opt != 'P' && sh_access(tab[0], 1) == 0)
		ret = chdir(tab[0]);
	free(tab[0]);
	free(dir);
	return (ret < 0 ? -1 : 0);
}
