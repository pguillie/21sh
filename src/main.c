#include "shell.h"

static void	sh_quit(void)
{
	struct termios	backup;

	ft_printf("\n\nToo many errors encountered, program has to quit.\n"
			"Press Enter to exit.");
	term_raw(&backup, 0, 1);
	while (key_input() != '\n')
		;
	tcsetattr(0, TCSANOW, &backup);
	ft_putchar('\n');
}

int			main(int ac, char *av[])
{
	t_tc	termcaps;
	t_token	*lexer;
	int		remaining_error;

	(void)ac;
	(void)av;

	if (sh_init(&termcaps))
		return (1);
	remaining_error = ERROR_MAX;
	while (remaining_error)
	{
		if (!(lexer = sh_hci(termcaps)))
			remaining_error -= 1;
	//	if (lexer_parser())
	//		return (1);
	//	if (execution())
	//		return (1);
	}
	
	sh_quit();
	return (0);
}
