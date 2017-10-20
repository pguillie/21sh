#include "shell.h"

int		sh_init_env(void)
{
	extern char	**environ;
	char		**dup;
//	char		*shlvl;
	int			ret;

	if (!(dup = sh_envdup(environ)))
		return (-1);
	ret = 1;
	environ = dup;
/*
	if ((shlvl = ft_itoa(ft_atoi(getenv("SHLVL") + 1))))
		ret = sh_setenv_name_val("SHLVL", shlvl); //secu
	else
		ret = 0;
	if (!getenv("SYNTAX_HIGHLIGHTING"))
		ret = sh_setenv_line("SYNTAX_HIGHLIGHTING=false");//secu
*/
	return (ret);
}
