#include "shell.h"

int		sh_hist(t_line **line, t_coord **coord, t_tc tc, t_line *target)
{
	(*line)->cur = sh_move_cur((*line)->cur, 0, *coord, tc);
	sh_clear(*line, *coord, tc);
	*line = target;
	free(*coord);
	if (!(*coord = sh_create_coord(*line, tc.prompt)))
		return (-1);
	(*line)->pos = (*line)->used;
	return (LEXER | DISP);
}
