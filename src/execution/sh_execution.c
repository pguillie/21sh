#include "shell.h"

int			sh_execution(char *av[], char *env[])
{
	if (ft_strequ(av[0], "echo"))
		return (sh_echo(av));
	else if (ft_strequ(av[0], "cd"))
		return (sh_cd(av));
	else if (ft_strequ(av[0], "setenv"))
		return (sh_setenv(av));
	else if (ft_strequ(av[0], "unsetenv"))
		return (sh_unsetenv(av));
	else if (ft_strequ(av[0], "env"))
		return (sh_env(av, env));
	else if (ft_strequ(av[0], "printenv"))
		return (sh_printenv(env));
	else
		return (sh_cmd_exec(av, env));
//	else if (ft_strequ(av[0], "exit"))
//		return (sh_exit(av, ret)); RECUPERER RET DEPUIS EXEC
}
