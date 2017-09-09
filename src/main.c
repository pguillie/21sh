#include "shell.h"

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
	while (remaining_error)
	{
		lexer = NULL;
		root = NULL;
		if (sh_hci(&termcaps, &lexer))
			remaining_error -= 1;
		else if (sh_parser(lexer, &root) < 0)
			remaining_error -= 1;
		else if ((ret = sh_tree_browse(root)) < 0)
			remaining_error -= 1;
	}
	ft_printf("\n\nToo many errors encountered, program has to quit.\n"
			"Press any key to exit.");
	ft_putchar('\n');
	return (1);
}
