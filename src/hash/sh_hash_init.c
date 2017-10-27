#include "shell.h"

int		sh_hash_init(void)
{
	t_htable	**htable;
	int			*hindex;
	int			i;

	htable = sh_htable();
	hindex = sh_hindex();
	ft_memset(htable, 0, sizeof(t_htable*) * HASH_SIZE);
	i = 0;
	while (i < HASH_SIZE)
		hindex[i++] = -1;
	return (0);
}
