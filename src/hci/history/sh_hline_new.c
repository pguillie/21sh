#include "shell.h"

t_line	*sh_hline_new(char *str, t_line *prev)
{
	t_line	*new;

	if (!(new = (t_line*)ft_memalloc(sizeof(t_line))))
		return (NULL);
	new->capacity = ((ft_strlen(str) + 1) / BUFF_SIZE + 1) * BUFF_SIZE;
	if (!(new->str = ft_strnew(new->capacity)))
	{
		ft_memdel((void**)new);
		return (NULL);
	}
	ft_strcat(new->st, str);
	new->used = ft_strlen(str);
	new->cur = 0;
	new->prev = prev;
	new->next = NULL;
	return (new);
}
