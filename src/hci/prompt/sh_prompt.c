#include "shell.h"

/*
**	en realite il y a =_4_TYPES_= de prompts
**	les 2 derniers sont des cas assez rares (genre plein de gens on du mourir sans jamais les avoir vu)
**	donc pour l'instant balek mais faudra ptetre voir pour plus tard
*/

int		sh_prompt(int mode)
{
	char	*ps[4];

	ps[0] = ft_strdup("\\e[01;32m\\u@\\h\\e[0m \\e[01;34m\\w \\$\\e[0m ");
	ps[1] = ft_strdup("> ");
	ps[2] = NULL;
	ps[3] = NULL;
	return (sh_print_prompt(ps[mode - 1]));
}
