#include "shell.h"

int		sh_list_del(t_cmd ****list, int **op)
{
	int		i;
	int		j;

	if (list && *list)
	{
		i = 0;
		while ((*list)[i])
		{
			j = 0;
			while ((*list)[i][j])
				sh_cmd_del(&(*list)[i][j++]);
			free((*list)[i]);
			(*list)[i++] = NULL;
		}
		free(*list);
		*list = NULL;
		list = NULL;
	}
	free(*op);
	op = NULL;
	return (-1);
}
