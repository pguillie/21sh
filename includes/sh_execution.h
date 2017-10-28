#ifndef SH_EXECUTION_H
# define SH_EXECUTION_H

int		sh_execution(char *av[], char *env[], int ret);
int		sh_cmd_exec(char *av[], char *env[], char **path);
int		sh_tree_browse(t_tree *root, int ret);
int		sh_redir_backup(int std[3]);
int		sh_redir_set(t_redir *redir, int fd[10]);
int		sh_redir_restore(int fd[10], int std[3]);

/*
**	SHAME
*/

int		sh_av_pipe(char *av[], char *env[], int ret);

#endif
