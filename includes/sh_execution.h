#include "shell.h"

int		sh_execution(char *av[]);
int		sh_tree_browse(t_tree *root);
int		sh_redir_init(int *std, int stdin, int stdout, int stderr);
int		sh_redir_restore(int *std, int stdin, int stdout, int stderr);

