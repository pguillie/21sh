#ifndef SH_BUILTINS_H
# define SH_BUILTINS_H

int		sh_echo(char *av[]);
int		sh_cd(char *av[]);
int		sh_setenv(char *av[]);
int		sh_setenv_var(char *prg, char *var);
int		sh_unsetenv(char *av[]);
int		sh_env(char *av[], char *env[]);
int		sh_exit(char *av[], int ret);
int		sh_printenv(char *env[], char *var);
int		sh_cd_opt(char *opt, char *str);
int		sh_concat_pwd(char **dir);
int		ft_access(char *dir, char *av, int mode);
int		sh_search_path(char **dir, char *av);

#endif
