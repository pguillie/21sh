#include "shell.h"

int		sh_edit_hist(t_line **line, long input, t_coord **coord, t_tc tc)
{
	(*line)->cur = sh_move_cur((*line)->cur, 0, *coord, tc);
	sh_del_afcur((*line), tc, *coord);
	*line = (input == K_UP || input == K_P_UP) ? (*line)->up : (*line)->down;
	free(*coord);
	if (!(*coord = sh_create_coord(*line, tc.prompt)))
		return (-1);
	sh_disp_line(*line, *coord, tc);
	(*line)->cur = sh_move_cur(0, (*line)->used, *coord, tc);
	return (0);
}
