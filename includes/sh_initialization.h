#ifndef SH_INITIALIZATION_H
# define SH_INITIALIZATION_H

int		sh_init(t_tc *init);
int		sh_init_env(void);
int		sh_init_termcaps(t_tc *init);
void	sh_init_loop(t_token **lexer, t_cmd ****list, int **op);

#endif
