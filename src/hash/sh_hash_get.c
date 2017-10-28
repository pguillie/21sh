#include "shell.h"

char	*sh_hash_get(char *cmd)
{
	t_htable	**htable;
	t_htable	*ctable;

	htable = sh_htable();
	ctable = htable[sh_hash_fct(cmd)];
	while (ctable && !ft_strequ(ctable->cmd, cmd))
		ctable = ctable->next;
	if (ctable)
		return (ctable->path);
	return (NULL);
}
