#ifndef SH_PARSER_H
# define SH_PARSER_H

# include "shell.h"

void	sh_cmd_del(t_cmd **cmd);
t_cmd	*sh_cmd_new(t_token *lexer);
int		sh_parser(t_token *lexer, t_tree **root);
int		sh_tree_del(t_tree **tree);
t_tree	*sh_tree_new(char *op, t_cmd *cmd);
int		sh_syntax(t_token *tree);

#endif
