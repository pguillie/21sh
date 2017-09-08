#include "shell.h"

static int	sh_exec_cmd_path(char *cmd, char **path)
{
	DIR				*dirp;
	struct dirent	*entry;
	char			**dir_path;
	size_t			i;
	int				found;

	if (!(dir_path = sh_envvarsplit(getenv("PATH"))))
		return (0);
	i = 0;
	found = 0;
	while (!found && dir_path[i])
	{
		if (!(dirp = opendir(dir_path[i])))
			return (-1);
		while ((entry = readdir(dirp)))
			if (ft_strequ(entry->d_name, cmd))
				found = 1;
		closedir(dirp);
		found == 0 ? i += 1 : 0;
	}
	found ? *path = ft_strcjoin(dir_path[i], cmd, '/') : 0;
	ft_strtabdel(dir_path);
	if (found)
		return (*path ? 1 : -1);
	return (0);
}

static int	sh_exec_cmd(char *cmd, char **path)
{
	struct stat	buf;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) < 0)
			return (0);
		if (stat(cmd, &buf) < 0)
			return (-1);
		if (S_ISDIR(buf.st_mode))
		{
			ft_error(cmd, "is a directory", NULL);
			return (0);
		}
		if (!(*path = ft_strdup(cmd)))
			return (-1);
		return (1);
	}
	return (sh_exec_cmd_path(cmd, path));
}

int			sh_execution(char *av[])
{
	pid_t		child;
	extern char **environ;
	char		*path;
	int			success;
	int			ret;

	path = NULL;
	ret = 0;
	if ((success = sh_exec_cmd(av[0], &path)) < 0)
		return (-1);
	ft_printf("path: %s\n", path);//
	if (success == 0)
		return (ft_error(av[0], "command not found", NULL));
	if (access(path, X_OK) < 0)
		return (ft_error(av[0], "permission denied", NULL));
	if ((child = fork()) < 0)
		return (-1);
	if (!child)
	{
		if (execve(path, av, environ) < 0)
			return (-1);
	}
	else
		waitpid(child, &ret, 0);
	return (ret);
}
