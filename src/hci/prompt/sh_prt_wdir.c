#include "shell.h"

int		sh_prt_wdir(char c)
{
	char	*wd;

	(void)c;
	wd = getenv("PWD");
	ft_putstr(wd);
	return (ft_strlen(wd));
}
