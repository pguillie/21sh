#include "shell.h"

int		sh_prompt_host(void)
{
	//je sais pas ou il est...
	char	*host = "42sh";

	ft_putstr(host);
	return (ft_strlen(host));
}
