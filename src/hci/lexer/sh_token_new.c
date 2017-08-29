#include "shell.h"

t_token		*sh_token_new(char *lexeme, int *status)
{
	t_token *new;

	if (!lexeme)
		return (NULL);
	if (!(new = ft_memalloc(sizeof(t_token))))
		return (NULL);
	new->lexeme = lexeme;
	new->category = sh_category(lexeme, status);
	new->next = NULL;
	return (new);
}
