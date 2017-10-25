#include "shell.h"

int		sh_token_del(t_token **begin)
{
	t_token	*tmp;

	if (*begin)
	{
		while (*begin)
		{
			tmp = (*begin)->next;
			ft_strdel(&(*begin)->lexeme);
			free(*begin);
			*begin = NULL;
			*begin = tmp;
		}
	}
	return (-1);
}
