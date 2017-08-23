#include "shell.h"

t_line	*sh_line_hist(t_line *line, t_line *new, t_coord **coord, t_tc tc)
{
	line->cur = sh_move_cur(line->cur, 0, *coord, tc);
	sh_del_after(line, tc, *coord);
	line = new;
	ft_putstr(line->str);
	free(*coord);
	*coord = sh_create_coord(line, tc.prompt);
	line->cur = line->used;
	return (line);
}
