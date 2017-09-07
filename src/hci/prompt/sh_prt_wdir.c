#include "shell.h"

int		sh_prt_wdir(char c)
{
	char	*wd;
	size_t	i;

	if (!(wd = getenv("PWD")))
		return (0);
	i = 0;
	if (c == 'W')
	{
		i = ft_strlen(wd);
		while (i && wd[i] != '/')
			i--;
		i ? i = i + 1 : 0;
	}
	ft_putstr(wd + i);
	return (ft_strlen(wd));
}
