#include "shell.h"

void	sh_clear(t_line *line, t_coord *coord, t_tc tc)
{
	size_t	i;

	tputs(tc.ce, 0, termput);
	i = line->cur;
	while (line->str[i] && coord[i].x)
		i++;
	if (coord[i].x == 0)
	{
		sh_move_cur(line->cur, i, coord, tc);
		tputs(tc.cd, 0, termput);
		sh_move_cur(i, line->cur, coord, tc);
	}
}
