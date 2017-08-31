#include "shell.h"

t_token		*sh_token_new(char *str, size_t *i, int *status)
{
	t_token *new;

	if (!(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	if (!(new->lexeme = ft_strsub(str, i[0], i[1])))
	{
		free(new);
		return (NULL);
	}
	new->category = sh_category(str, i, status);
	new->next = NULL;
	return (new);
}
