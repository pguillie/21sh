#include "shell.h"

int		sh_tree_del(t_tree **tree)
{
	if ((*tree)->left)
		sh_tree_del(&((*tree)->left));
	if ((*tree)->right)
		sh_tree_del(&((*tree)->right));
	(*tree)->op ? ft_strdel(&((*tree)->op)) : 0;
	(*tree)->cmd ? sh_cmd_del(&((*tree)->cmd)) : 0;
	ft_memdel((void**)tree);
	return (-1);
}
