#include "shell.h"

t_token		*sh_token_new(char *str, size_t *i)
{
	t_token *new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	new->lexeme = ft_strsub(str, i[0], i[1]);
	new->category = sh_category(new->lexeme);
	new->next = NULL;
	return (new);
}
