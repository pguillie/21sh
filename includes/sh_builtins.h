#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

int		sh_echo(char *av[]);
int		sh_setenv(char *av[]);
int		sh_setenv_var(char *var);
int		sh_unsetenv(char *av[]);
int		sh_env(char *av[], char *env[]);
int		sh_exit(char *av[], int ret);
int		sh_printenv(char *env[]);

#endif
