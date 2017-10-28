#ifndef SH_PARSER_H
# define SH_PARSER_H

# include "shell.h"

t_cmd	*sh_cmd_new(t_token *lexer);
void	sh_cmd_del(t_cmd **cmd);

#endif
