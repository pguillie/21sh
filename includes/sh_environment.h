#ifndef SH_ENVIRONMENT_H
# define SH_ENVIRONMENT_H

char	**sh_envdup(char *env[]);
char	**sh_envvarsplit(char *name, char *env[]);
char	*sh_getenv(char *name, char *env[]);

#endif
