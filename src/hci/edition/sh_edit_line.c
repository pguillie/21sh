#include "shell.h"

static int	sh_nl(t_line *line, t_coord **coord, t_tc tc)
{
	line->cur = sh_move_cur(line->cur, line->used, *coord, tc);
	if (sh_ins(line, coord, tc, '\n') < 0)
		return (-1);
	return (EOL | LEXER | DISP);
}

int		sh_edit_line(t_line **line, char **save, t_token **lexer, t_tc *tc)
{
	t_coord	*coord;
	int		success[2];
	char	byte;
	char	*tmp;

	tmp = NULL;
	if (!(coord = sh_create_coord(*line, tc->prompt)))
		return (-1);
	success[0] = 0;
	while (!sh_sig_quit() && !(success[0] & EOL))
	{
		tmp ? ft_strdel(&tmp) : 0;
		if (read(0, &byte, 1) < 0)
			return (-1);
		if (byte == 27)
			success[0] = sh_esc(line, &coord, tc);
		else if (byte == '\n')
			success[0] = sh_nl(*line, &coord, *tc);
		else if (byte == 127)
			success[0] = sh_del_l(*line, &coord, *tc);
		else
			success[0] = sh_ins(*line, &coord, *tc, byte);
		if (success[0] < 0)
			return (success[0]);
		if (success[0] & LEXER)
		{
			if (!(tmp = ft_strjoin(*save, (*line)->str)))
				return (-1);
			if ((success[1] = sh_lexer(tmp, lexer)) < 0)
				return (-1);
		}
		if (success[0] & DISP)
			sh_display(*line, coord, *tc); //+lexer
	}
	free(coord);
	*save ? ft_strdel(save) : 0;
	*save = tmp;
	return (success[1]);
}
