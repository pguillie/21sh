#include "shell.h"

static int	sh_nl(t_line *line, t_coord **coord, t_tc tc)
{
	line->cur = sh_move_cur(line->cur, line->used, *coord, tc);
	if (sh_ins(line, coord, tc, '\n') < 0)
		return (-1);
	return (EOL | LEXER | DISP);
}

static int	sh_nor(t_line **line, char *save, t_coord **coord, t_tc *tc)
{
	char	byte;
	int		ret;

	ret = -1;
	if (read(0, &byte, 1) < 0)
		return (-1);
	else if (byte == 4)
		ret = sh_ctrl_d(line, coord, tc, save);
	else if (byte == 27)
		ret = sh_esc(line, coord, tc);
	else if (byte == '\n')
		ret = sh_nl(*line, coord, *tc);
	else if (byte == 127)
		ret = sh_del_l(*line, coord, *tc);
	else if (byte >= 32 && byte < 127)
		ret = sh_ins(*line, coord, *tc, byte);
	return (ret);
}

static void	petite_fonction_free(t_coord **coord, char **save, char *tmp)
{
	free(*coord);
	*save ? ft_strdel(save) : 0;
	*save = tmp;
}

int			sh_edit_line(t_line **line, char **save, t_token **lexer, t_tc *tc)
{
	t_coord	*coord;
	int		success[2];
	char	*tmp;

	tmp = NULL;
	success[0] = 0;
	if (!(coord = sh_create_coord(*line, tc->prompt)))
		return (-1);
	while (g_signal != SIGINT && !(success[0] & EOT) && !(success[0] & EOL))
	{
		tmp ? ft_strdel(&tmp) : 0;
		if ((success[0] = sh_nor(line, *save, &coord, tc)) & LEXER)
		{
			if (!(tmp = ft_strjoin(*save, (*line)->str)))
				return (-1);
			if ((success[1] = sh_lexer(tmp, lexer)) < 0)
				return (-1);
		}
		if (success[0] & DISP)
			sh_display(*line, coord, *tc);
	}
	petite_fonction_free(&coord, save, tmp);
	if (success[0] < 0)
		return (-1);
	return (success[1] = success[0] & EOT ? EOT : success[1]);
}
