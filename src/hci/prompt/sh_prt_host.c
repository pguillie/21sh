#include "shell.h"

int		sh_prt_host(char c)
{
	char	host[1024];
	size_t	i;

	ft_memset(host, 0, 1024);
	if (gethostname(host, 1024) < 0)
		return (0);
	i = 0;
	while (i < 1024 && (c == 'h' ? host[i] != '.' : 1))
		i++;
	host[i] = '\0';
	ft_putstr(host);
	return (ft_strlen(host));
}
