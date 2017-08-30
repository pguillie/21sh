#include "shell.h"

static char	**sh_splitalloc(char *value)
{
	char	**ret;
	size_t	i;
	size_t	colon;

	i = 0;
	colon = 3;
	while (value && value[i])
		if (value[i++] == ':')
			colon += 1;
	ret = (char**)ft_memalloc(sizeof(char*) * colon);
	return (ret);
}

static char	*sh_splitnew(char *value, size_t i, size_t l)
{
	if (l > 0)
		return (ft_strsub(value, i, l));
	return (ft_strdup("."));
}

static char	**sh_splitexit(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		ft_strdel(&array[i++]);
	ft_memdel((void**)&array);
	return (NULL);
}

char		**sh_envvarsplit(char *name, char *env[])
{
	char	**new;
	char	*value;
	size_t	i[3];

	value = sh_getenv(name, env);
	if (!(new = sh_splitalloc(value)))
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	if (value)
	{
		if (value[i[0]] == ':')
			i[0]++;
		while (value[i[0]])
		{
			i[2] = 0;
			while (value[i[0] + i[2]] && value[i[0] + i[2]] != ':')
				i[2]++;
			if (!(new[i[1]++] = sh_splitnew(value, i[0], i[1])))
				return (sh_splitexit(new));
			i[0] += value[i[0] + i[2]] ? i[2] + 1 : i[2];
		}
	}
	new[i[1]] = ft_strdup(".");
	return (new);
}
