#include "shell.h"

int		sh_prompt_workdir(void)
{
	char	*wd;

	wd = getenv("PWD");
	ft_putstr(wd);
	return (ft_strlen(wd));
}
