#include "shell.h"

void	sh_disp_line(t_line *line, t_coord *coord, t_tc tc)
{
	ft_putstr(line->str + line->cur);
	if (coord[line->used - 1].x == coord[line->used + 1].x - 1
			&& coord[line->cur].x != coord[line->used].x)
		ft_putchar('\n');
	line->cur = sh_move_cur(line->used, line->cur, coord, tc);
}
