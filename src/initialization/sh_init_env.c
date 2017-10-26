#include "shell.h"

static int	sh_init_env_free(char *a, char *b, char *c)
{
	a ? free(a) : 0;
	b ? free(b) : 0;
	c ? free(c) : 0;
	return (-1);
}

int			sh_init_env(void)
{
	extern char	**environ;
	char		*shlvl;
	char		*pwd;
	char		*str;

	if (!(environ = sh_envdup(environ)))
		return (-1);
	shlvl = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
	pwd = getcwd(NULL, PATH_SIZE);
	str = ft_strjoin("SHLVL=", shlvl);
	if (!shlvl || !pwd || !str)
		return (sh_init_env_free(pwd, shlvl, str));
	sh_setenv_var("setenv", str);
	free(str);
	if (!(str = ft_strjoin("PWD=", pwd)))
		return (sh_init_env_free(pwd, shlvl, str));
	sh_setenv_var("setenv", str);
	sh_init_env_free(str, shlvl, pwd);
	return (1);
}
