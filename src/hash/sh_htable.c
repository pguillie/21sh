#include "shell.h"

t_htable	**sh_htable(void)
{
	static t_htable	*htable[HASH_SIZE];

	return (htable);
}
