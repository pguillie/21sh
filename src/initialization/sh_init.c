#include "shell.h"

int		sh_init(t_tc *init)
{
	extern char **environ;
	int			success;

	success = sh_init_env();
	if (success < 0)
		return (ft_error("Unable to duplicate environment", NULL, NULL));
	else if (success == 0)
		ft_error("Warning",
				"Some environment variables could not get set", NULL);
	if (sh_init_termcaps(init))
	{
		ft_error("Warning", "Line edition can't switch to advanced mode", NULL);
		init->on = 0;
	}
	else
		init->on = 1;
	sh_hash_init();//
	return (0);
}
