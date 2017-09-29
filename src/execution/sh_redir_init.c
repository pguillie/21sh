#include "shell.h"

int		sh_redir_init(int *std, int stdin, int stdout, int stderr)
{
	if (stdin)
		std[0] = dup(0);
	if (stdout)
		std[1] = dup(1);
	if (stderr)
		std[2] = dup(2);
	return ((stdin && std[0] < 0) || (stdout && std[1] < 0)
			|| (stderr && std[2] < 0));
}
