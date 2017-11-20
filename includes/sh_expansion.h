#ifndef SH_EXPANSION_H
# define SH_EXPANSION_H

t_token	*sh_expansion(t_token *lexer);
char	*sh_exp_tilde(char *lexeme);
char	*sh_rm_quote(char *lex);

#endif
