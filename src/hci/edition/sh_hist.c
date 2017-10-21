#include "shell.h"

int		sh_hist(t_line **line, t_coord **coord, t_tc tc, t_line *target)
{
	(*line)->cur = sh_move_cur((*line)->cur, 0, *coord, tc);
	target->h_smd = (*line)->h_smd;
	target->h_pos = (*line)->h_pos;
	*line = target;
	(*line)->pos = (*line)->used;
	return (LEXER | DISP);
}
