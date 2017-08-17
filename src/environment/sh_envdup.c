#include "shell.h"

char	**sh_envdup(char *env[])
{
	char	**new;
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	if (!(new = (char**)ft_memalloc(sizeof(char*) * (i + 1))))
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!(new[i] = ft_strdup(env[i])))
		{
			while (i--)
				ft_strdel(&new[i]);
			ft_memdel((void**)&new);
			return (NULL);
		}
		i++;
	}
	return (new);
}
