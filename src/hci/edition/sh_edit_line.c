#include "shell.h"

static int	sh_nl(t_line *line, t_coord **coord, t_tc tc)
{
	line->cur = sh_move_cur(line->cur, line->used, *coord, tc);
	if (sh_ins(line, '\n') < 0)
		return (-1);
	return (EOL | LEXER | DISP);
}

static int	sh_norme1(t_line **line, char *save, t_tc *tc)
{
	int		ret;
	char	byte;
	int		hist_search_mode;

	ret = 0;
	byte = 0;
	hist_search_mode = 0;
	if (read(0, &byte, 1) < 0 && g_signal != SIGWINCH)
		return (-1);
	else if (byte == 11 || byte == 21 || byte == 23 || byte == 25)
		ret = sh_cvx(*line, &tc->coord, tc, byte);
	else if (byte == 27)
		ret = sh_esc(line, &tc->coord, tc, &hist_search_mode);
	else if (byte == 4)
		ret = sh_ctrl_d(*line, save);
	else if (byte == '\n')
		ret = sh_nl(*line, &tc->coord, *tc);
	else if (byte == 127)
		ret = sh_del_l(*line, &tc->coord, *tc);
	else if (byte >= 32 && byte < 127)
		ret = sh_ins(*line, byte);
	(*line)->h_smd = hist_search_mode;
	if (((byte != 11 && byte != 21 && byte != 23 && byte != 25)))
		tc->cut = 0;
	return (ret);
}

static int	sh_norme2(t_line *line, char *save, t_tc *tc, int success)
{
	if (g_signal == SIGWINCH)
	{
		free(tc->coord);
		if (!(tc->coord = sh_create_coord(line, tc->prompt)))
			return (-1);
	}
	if (success & DISP)
	{
		if (success & (DISP_FULL ^ DISP))
		{
			line->pos = line->cur;
			line->cur = 0;
			sh_prompt(save ? 2 : 1);
		}
		if (sh_display(line, &(tc->coord), *tc) < 0)
			return (-1);
	}
	return (0);
}

static int	sh_edit_free(t_coord *coord, int *success)
{
	free(coord);
	if (success[0] & EOT || success[0] < 0)
		return (success[0]);
	return (success[1]);
}

int			sh_edit_line(t_line **line, char *save, t_tc *tc)
{
	int		success[2];

	success[0] = 0;
	if (!(tc->coord = sh_create_coord(*line, tc->prompt)))
		return (-1);
	while (g_signal != SIGINT && !(success[0] & EOT) && !(success[0] & EOL)
			&& !(success[0] < 0))
	{
		success[0] = sh_norme1(line, save, tc);
		if (g_signal == SIGINT)
			sh_move_cur((*line)->cur, (*line)->used, tc->coord, *tc);
		else if (sh_norme2(*line, save, tc, success[0]) < 0)
			return (-1);
	}
	return (sh_edit_free(tc->coord, success));
}
