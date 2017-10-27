#include "shell.h"

int		sh_hash_fct(char *cmd)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (cmd[i])
		ret += cmd[i++];
	return (ret % HASH_SIZE);
}
