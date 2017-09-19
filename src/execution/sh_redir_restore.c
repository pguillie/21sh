#include "shell.h"

int		sh_redir_restore(int *std, int stdin, int stdout, int stderr)
{
	int	error;

	error = 0;
	if (stdin)
		if (dup2(std[0], 0) < 0)
			error = -1;
	if (stdout)
		if (dup2(std[1], 1) < 0)
			error = -1;
	if (stderr)
		if (dup2(std[2], 2) < 0)
			error = -1;
	return (error);
}
