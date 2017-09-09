#include "shell.h"

int			main(void)
{
	t_tc	termcaps;
	t_token	*lexer;
	t_tree	*root;
	int		remaining_error;

	if (sh_init(&termcaps))
		return (1);
	remaining_error = ERROR_MAX;
	while (remaining_error)
	{
		lexer = NULL;
		if (sh_hci(&termcaps, &lexer))
			remaining_error -= 1;
		displex(lexer);
		root = NULL;
		if (sh_parser(lexer, &root) < 0)
			remaining_error -= 1;
	if (root)
		disptree(root);
	//	if (execution())
	//		return (1);
	}
	ft_printf("\n\nToo many errors encountered, program has to quit.\n"
			"Press any key to exit.");
	ft_putchar('\n');
	return (1);
}
