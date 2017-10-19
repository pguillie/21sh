#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

int		sh_builtins(char *av[]);
int		sh_echo(char *av[]);
int		sh_setenv(char *av[]);
int		sh_setenv_var(char *var);

#endif
