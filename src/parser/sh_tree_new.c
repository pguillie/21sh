#include "shell.h"

t_tree	*sh_tree_new(char *op, t_cmd *cmd)
{
	t_tree *new;

	if (!(new = (t_tree*)ft_memalloc(sizeof(t_tree))))
		return (NULL);
	if (!(new->cmd = cmd))
		return (NULL);
	if (!(new->op = ft_strdup(op)))
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	return (new);
}
