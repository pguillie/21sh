#include "shell.h"

int		main(int ac, char *av[])
{
	t_tc	termcaps;
	t_token	*lexer;

	(void)ac;
	(void)av;
	if (sh_init(&termcaps))
		return (1);
	lexer = NULL;
	while (1)
	{
		if (!(lexer = sh_hci(termcaps)))
			return (1);
	//	if (lexer_parser())
	//		return (1);
	//	if (execution())
	//		return (1);
	}
	return (0);
}
