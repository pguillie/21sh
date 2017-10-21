#include "shell.h"

static int	sh_prt_patch(char buff[], int *b)
{
	char	*patch;
	int		i;

	patch = PATCH;
	if (*b == PRT_SIZE)
		*b = ft_flush_buff(buff, PRT_SIZE);
	buff[(*b)++] = '.';
	i = 0;
	while (patch[i])
	{
		if (*b == PRT_SIZE)
			*b = ft_flush_buff(buff, PRT_SIZE);
		buff[(*b)++] = patch[i++];
	}
	return (i + 1);
}

int			sh_prt_vers(char buff[], int *b, char r)
{
	char	*version;
	int		i;

	version = VERSION;
	i = 0;
	while (version[i])
	{
		if (*b == PRT_SIZE)
			*b = ft_flush_buff(buff, PRT_SIZE);
		buff[(*b)++] = version[i++];
	}
	if (r == 'V')
		i += sh_prt_patch(buff, b);
	return (i);
}
