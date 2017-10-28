#include "shell.h"

int		sh_putesc(t_line **line, t_coord **coord, t_tc *tc, int *hist_search)
{
	t_line	*target;
	int		ret;

	ret = 0;
	if (sh_move_able(tc->esc, *line, *coord, hist_search))
		(*line)->cur = sh_move_cur((*line)->cur, (*line)->pos, *coord, *tc);
	else if ((target = sh_hist_able(tc->esc, *line, hist_search)) != *line)
		ret = sh_hist(line, coord, *tc, target);
	else if (sh_del_able(tc->esc, *line))
		ret = sh_del_r(*line);
	else if (tc->esc[1] == '\n')
		ret = sh_ins(*line, '\n');
	free(tc->esc);
	return (ret);
}
