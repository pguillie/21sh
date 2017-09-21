#include "shell.h"

static int	sh_exec_file(char *cmd, char **path)
{
	struct stat		buf;

	if (access(cmd, F_OK) < 0)
		return (ft_error(cmd, E_NOENT, NULL));
	if (stat(cmd, &buf) < 0)
		return (-1);
	if (S_ISDIR(buf.st_mode))
		return (ft_error(cmd, "Is a directory", NULL));
	if (access(cmd, X_OK) < 0)
		return (ft_error(cmd, "Permission denied", NULL));
	if (!(*path = ft_strdup(cmd)))
		return (-1);
	return (0);
}

static int	sh_exec_dir(char *cmd, char *dir)
{
	DIR				*dirp;
	struct dirent	*entry;
	int				ret;

	ret = 0;
	if ((dirp = opendir(dir)))
	{
		while ((entry = readdir(dirp)))
			if (ft_strequ(entry->d_name, cmd))
				ret = 1;
		closedir(dirp);
	}
	return (ret);
}

static int	sh_exec_bin(char *cmd, char **path)
{
	char	**env_path;
	char	*path_value;
	size_t	i;
	int		found;

	if (!(path_value = getenv("PATH")))
		return (ft_error(cmd, E_NOCMD, NULL));
	if (!(env_path = sh_envvarsplit(path_value)))
		return (-1);
	i = 0;
	found = 0;
	while (env_path[i + 1] && !found)
		if (sh_exec_dir(cmd, env_path[i++]))
			found = 1;
	if (found)
		*path = ft_strcjoin(env_path[i - 1], cmd, '/');
	ft_strtabdel(env_path);
	if (!found)
		return (ft_error(cmd, E_NOCMD, NULL));
	else if (!*path)
		return (-1);
	if (access(*path, X_OK) < 0 && ft_error(cmd, "Permission denied", NULL))
		ft_strdel(path);
	return (*path ? 0 : 1);
}

int			sh_execution(char *av[])
{
	pid_t		child;
	extern char **environ;
	char		*path;
	int			no_file;
	int			ret;

	path = NULL;
	ret = 0;
	if ((no_file = ft_strchr(av[0], '/') ?
		sh_exec_file(av[0], &path) : sh_exec_bin(av[0], &path)) < 0)
		return (-1);
	if (no_file)
		return (1);
	if ((child = fork()) < 0)
		return (-1);
	if (child == 0)
	{
		if (execve(path, av, environ) < 0)
			return (-1);
	}
	else
		waitpid(child, &ret, 0);
	ft_strdel(&path);
	return (ret);
}
