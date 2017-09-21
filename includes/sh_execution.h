#include "shell.h"

int		sh_execution(char *av[]);
int		sh_tree_browse(t_tree *root);
int		sh_redir_set(t_redir *redir, int std[]);
void	sh_redir_restore(int std[]);
