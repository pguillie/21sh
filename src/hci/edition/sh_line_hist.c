#include "shell.h"

t_line	*sh_line_hist(t_line *line, t_line *new, t_coord *coord, t_tc tc)
{
	line->cur = sh_move_cur(line->cur, 0, coord, tc);
	tputs(tc.ce, 0, termput);//
	line = new;
	ft_putstr(line->str);
	line->cur = line->used;
	return (line);
}
