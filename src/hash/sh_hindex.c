#include "shell.h"

int		*sh_hindex(void)
{
	static int	hindex[HASH_SIZE];

	return (hindex);
}
