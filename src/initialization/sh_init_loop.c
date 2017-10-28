#include "shell.h"

int		sh_init_loop(t_token **lexer, t_cmd ****list, int **op)
{
	g_signal = 0;
	*lexer = NULL;
	*list = NULL;
	*op = NULL;
	return (0);
}
