#include "shell.h"

void	sh_hash_free(void)
{
	t_htable	**htable;
	t_htable	*ctable;
	t_htable	*tmp;
	int			*hindex;
	int			i;

	i = 0;
	htable = sh_htable();
	hindex = sh_hindex();
	while (hindex[i] >= 0)
	{
		ctable = htable[hindex[i]];
		while (ctable)
		{
			free(ctable->cmd);
			free(ctable->path);
			tmp = ctable->next;
			free(ctable);
			ctable = tmp;
		}
		i++;
	}
	sh_hash_init();
}
