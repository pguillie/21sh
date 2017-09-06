#include "shell.h"

int		sh_edit_line(t_line **line, char **save, t_token **lexer, t_tc *tc)
{
	t_coord	*coord;
	int		success;
	char	byte;

	if (!(coord = sh_create_coord(*line, tc->prompt)))
		return (-1);
	success = 0;
	while (!(success & EOL))
	{
		if (read(0, &byte, 1) < 0)
			return (-1);
		if (byte == 27)
			success = sh_esc(line, &coord, tc);
	//	else if (byte == '\n')
	//		success = sh_edit_nl(*line, &coord, *tc);
		else if (byte == 127)
			success = sh_del_l(*line, &coord, *tc);
		else
			success = sh_ins(*line, &coord, *tc, byte);
		if (success < 0)
			return (success);
		if (success & LEXER)
			;//lexer
		if (success & DISP)
			sh_display(*line, coord, *tc); //+lexer
	}
	(void)save;
	(void)lexer;
	return (0);
}
