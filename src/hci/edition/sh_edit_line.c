#include "shell.h"

int		sh_edit_line(t_line **line, char **save, t_token **lexer, t_tc *tc)
{
	t_coord	*coord;
	char	byte;

	if (!(coord = sh_create_coord(*line, tc->prompt)))
		return (-1);
	byte = 0;
	while (byte != '\n')
	{
		if (read(0, &byte, 1) < 0)
			return (-1);
		if (byte == 27 && sh_esc(line, coord, tc) < 0)
				return (-1);
		else if (byte == 127)
			sh_del(*line, &coord, *tc);
		else
			sh_ins(*line, &coord, *tc, byte);
	}
	(void)save;
	(void)lexer;
	(void)tc;
	return (0);
}
