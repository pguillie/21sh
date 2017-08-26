#include "shell.h"

t_line	*sh_line_hist(t_line *line, t_line *new, t_coord **coord, t_tc tc)
{
	line->cur = sh_move_cur(line->cur, 0, *coord, tc);
	sh_del_after(line, tc, *coord);
	line = new;
	free(*coord);
	*coord = sh_create_coord(line, tc.prompt);
	sh_disp_line(line, *coord, tc);
	line->cur = sh_move_cur(0, line->used, *coord, tc);
	return (line);
}
