#include "shell.h"

int			main(void)
{
	t_tc	termcaps;
	t_token	*lexer;
	int		remaining_error;

	if (sh_init(&termcaps))
		return (1);
	remaining_error = ERROR_MAX;
	while (remaining_error)
	{
		if (!(lexer = sh_hci(&termcaps)))
			remaining_error -= 1;
	//	if (lexer_parser())
	//		return (1);
	//	if (execution())
	//		return (1);
	}
	ft_printf("\n\nToo many errors encountered, program has to quit.\n"
			"Press any key to exit.");
	ft_putchar('\n');
	return (1);
}
