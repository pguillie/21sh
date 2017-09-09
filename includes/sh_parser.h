#ifndef SH_PARSER_H
# define SH_PARSER_H

# include "shell.h"

int		sh_parser(t_token *lexer, t_tree **root);
t_cmd	*sh_cmd_new(t_token *lexer);
void	sh_cmd_del(t_cmd **cmd);
t_tree	*sh_tree_new(char *op, t_cmd *cmd);
int		sh_tree_del(t_tree **tree);

#endif
