#include "shell.h"

int		sh_init(t_tc *init)
{
	int			success;

	if (sh_init_env() < 0)
		return (ft_error("Unable to initialize environment", NULL, NULL));
	if (sh_init_termcaps(init))
		ft_error("Warning", "Line edition can't switch to advanced mode", NULL);
	sh_hash_init();
	return (0);
}
