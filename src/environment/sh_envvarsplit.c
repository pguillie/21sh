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

char		**sh_envvarsplit(char *value)
{
	char	**new;
	size_t	i;
	size_t	j;
	size_t	l;

	if (!(new = sh_splitalloc(value)))
		return (NULL);
	i = 0;
	j = 0;
	if (value)
	{
		if (value[i] == ':')
			i++;
		while (value[i])
		{
			l = 0;
			while (value[i + l] && value[i + l] != ':')
				l++;
			if (!(new[j++] = sh_splitnew(value, i, l)))
				return (sh_splitexit(new));
			i += value[i + l] ? l + 1 : l;
		}
	}
	new[j] = ft_strdup(".");
	return (new);
}
