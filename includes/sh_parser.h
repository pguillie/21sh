#ifndef SH_PARSER_H
# define SH_PARSER_H

# include "shell.h"

int		sh_parser(t_token *lexer, t_cmd ****list, int **op);
int		sh_list_del(t_cmd ****cmd_list, int **op);
t_cmd	*sh_cmd_new(t_token *lexer);
void	sh_cmd_del(t_cmd **cmd);

#endif
