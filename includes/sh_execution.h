#ifndef SH_EXECUTION_H
# define SH_EXECUTION_H

# include "shell.h"

int		sh_execution(char *av[], char *env[], int ret);
int		sh_cmd_exec(char *av[], char *env[]);
int		sh_tree_browse(t_tree *root, int ret);
int		sh_redir_set(t_redir *redir, int std[], int *fd);
void	sh_redir_restore(int std[], int fd);

#endif
