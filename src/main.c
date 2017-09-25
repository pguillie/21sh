#include "shell.h"

/*
**	The return status (see Exit Status) of a simple command is its exit status
**	as provided by the POSIX 1003.1 waitpid function,
**	or 128+n if the command was terminated by signal n.
*/

static void	sh_set_to_zero(t_token **lexer, t_tree **root, int mode)
{
	if (mode == 1)
	{
		g_signal = 0;
		*lexer = NULL;
		*root = NULL;
	}
	else if (mode == 2)
	{
		*lexer ? sh_token_del(lexer) : 0;
		*root ? sh_tree_del(root) : 0;
	}
}

int			main(void)
{
	t_tc	termcaps;
	t_token	*lexer;
	t_tree	*root;
	int		remaining_error;
	int		ret;

	if (sh_init(&termcaps))
		return (1);
	remaining_error = ERROR_MAX;
	sh_catch_signals();
	while (remaining_error)
	{
		sh_set_to_zero(&lexer, &root, 1);
		if (sh_hci(&termcaps, &lexer, ret))
			remaining_error -= 1;
		else if (sh_parser(lexer, &root) < 0)
			remaining_error -= 1;
		else if ((ret = sh_tree_browse(root)) < 0)
			remaining_error -= 1;
		sh_set_to_zero(&lexer, &root, 2);
	}
	ft_printf("\n\nToo many errors encountered, program has to quit.\n");
	return (1);
}
