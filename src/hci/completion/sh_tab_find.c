#include "shell.h"

static void	sh_tab_append(char **array[], char *occ, char c)
{
	char	**new;
	size_t	i;

	i = 1;
	if (*array)
		while ((*array)[i])
			if (ft_strequ((*array)[i++], occ))
				return ;
	if ((new = (char**)ft_memalloc(sizeof(char*) * (i + 2))))
	{
		if ((new[i] = ft_strnew(ft_strlen(occ) + 1)))
		{
			ft_strcpy(new[i], occ);
			ft_strncat(new[i], &c, 1);
			while (i--)
				new[i] = (*array)[i];
			free(*array);
			*array = new;
		}
		else
			free(new);
	}
}

static void	sh_tab_norminette(char path[], char *dir, char *fil)
{
	ft_strncpy(path, dir, PATH_SIZE);
	ft_strlcat(path, "/", PATH_SIZE);
	ft_strlcat(path, fil, PATH_SIZE);
}

static void	sh_tab_open(char **array[], char *dir, int cat)
{
	DIR				*dirp;
	struct dirent	*de;
	struct stat		buf;
	char			path[PATH_SIZE];
	size_t			len;

	if ((dirp = opendir(dir)))
	{
		len = ft_strlen(sh_rm_quote(*array[0]));
		while ((de = readdir(dirp)))
		{
			if (ft_strnequ(sh_rm_quote(*array[0]), de->d_name, len)
					&& !ft_strequ(de->d_name, "..")
					&& !ft_strequ(de->d_name, "."))
			{
				sh_tab_norminette(path, dir, de->d_name);
				if (stat(path, &buf) == 0
						&& (cat != CMD || S_ISDIR(buf.st_mode)
							|| S_IXUSR & buf.st_mode))
					sh_tab_append(array, de->d_name, S_ISDIR(buf.st_mode)
							? '/' : 0);
			}
		}
		closedir(dirp);
	}
}

static void	sh_tab_builtin(char **array[])
{
	size_t	len;

	len = ft_strlen(*array[0]);
	if (ft_strnequ(*array[0], "echo", len))
		sh_tab_append(array, "echo", 0);
	if (ft_strnequ(*array[0], "cd", len))
		sh_tab_append(array, "cd", 0);
	if (ft_strnequ(*array[0], "setenv", len))
		sh_tab_append(array, "setenv", 0);
	if (ft_strnequ(*array[0], "unsetenv", len))
		sh_tab_append(array, "unsetenv", 0);
	if (ft_strnequ(*array[0], "env", len))
		sh_tab_append(array, "env", 0);
	if (ft_strnequ(*array[0], "exit", len))
		sh_tab_append(array, "exit", 0);
	if (ft_strnequ(*array[0], "printenv", len))
		sh_tab_append(array, "printenv", 0);
}

char		**sh_tab_find(char *array[], char *dir, int category)
{
	char	**path;
	size_t	i;

	if (category == CMD && ft_strequ(dir, "."))
	{
		i = 0;
		path = NULL;
		if (!(path = sh_envvarsplit(getenv("PATH"))))
			return (NULL);
		while (path[i])
		{
			sh_tab_open(&array, path[i], category);
			i += 1;
		}
		ft_strtabdel(path);
		sh_tab_builtin(&array);
	}
	else
		sh_tab_open(&array, dir, category);
	return (array);
}
