#include "shell.h"

static char		*sh_get_ptr_path(void)
{
	int			i;
	extern char **environ;

	i = 0;
	while (environ[i])
	{
		if (ft_strnequ(environ[i], "PATH", 4) && environ[i][4] == '=')
			return (environ[i]);
		i++;
	}
	return (NULL);
}

void			sh_init_loop(t_token **lexer, t_cmd ****list, int **op)
{
	static char	*old_path = NULL;
	char		*new_path;

	new_path = sh_get_ptr_path();
	if (old_path != new_path)
	{
		old_path = new_path;
		sh_hash_free();
	}
	g_signal = 0;
	*lexer = NULL;
	*list = NULL;
	*op = NULL;
}
