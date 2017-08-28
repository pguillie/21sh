#include "shell.h"

t_token	*sh_token_del(t_token **begin)
{
	t_token	*tmp;

	while (*begin)
	{
		tmp = (*begin)->next;
		ft_strdel(&(*begin)->lexeme);
		ft_memdel((void**)begin);
		*begin = tmp;
	}
	return (NULL);
}
