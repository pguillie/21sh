#include "shell.h"

void	sh_hash_disp(void)
{
	t_htable	**htable;
	t_htable	*ctable;
	int			*hindex;
	int			i;

	htable = sh_htable();
	hindex = sh_hindex();
	i = 0;
	if (hindex[0] < 0)
		ft_putendl("hash table is empty");
	else
	{
		while (hindex[i] >= 0)
		{
			ctable = htable[hindex[i]];
			while (ctable)
			{
				ft_putendl(ctable->path);
				ctable = ctable->next;
			}
			i++;
		}
	}
}
