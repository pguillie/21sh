#include "shell.h"

int		main(int ac, char *av[])
{
	t_super	*super_struct;

	if (init())
		return (1);
/*
	while (1)
	{
		if (hci())
			return (1);
		if (lexer_parser())
			return (1);
		if (execution())
			return (1);
	}
*/
	return (1);
}
