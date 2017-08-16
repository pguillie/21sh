#include "shell.h"

int		sh_init_env(void)
{
	extern char	**environ;
	char		**dup;
	char		*shlvl;

	if (!(dup = sh_envdup(environ)))
		return (-1);
	if ((shlvl = ft_itoa(ft_atoi(getenv("SHLVL") + 1))))
		sh_setenv_name_val("SHLVL", shlvl); //secu
	else
		ft_error("Warning",
			"`SHLVL' environment variable could not be increased", NULL);
	if (!getenv("SYNTAX_HIGHLIGHTING"))
		sh_setenv_line("SYNTAX_HIGHLIGHTING=false");//secu
	return (0);
}
