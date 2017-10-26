#include "shell.h"

/*
**	The return status (see Exit Status) of a simple command is its exit status
**	as provided by the POSIX 1003.1 waitpid function,
**	or 128+n if the command was terminated by signal n.
*/

//ret est pas init

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
		sh_init_loop(&lexer, &root);
		if (sh_hci(&termcaps, &lexer, ret))
			remaining_error -= 1;
		else if (sh_parser(sh_expansion(lexer), &root) < 0)
			remaining_error -= 1;
		else if ((ret = sh_tree_browse(root, ret)) < 0)
			remaining_error -= 1;
		lexer ? sh_token_del(&lexer) : 0;
		root ? sh_tree_del(&root) : 0;
	}
	ft_printf("\n\nToo many errors encountered, program has to quit.\n");
	return (1);
}
