#include "shell.h"

void	sh_display(t_line *line, t_coord *coord, t_tc tc)
{
	size_t	i;

	sh_clear(line, coord, tc);
	i = line->cur;
	while (line->str[i])
	{
		ft_putchar_fd(line->str[i++], 0);
		if (line->str[i - 1] != '\n' && line->cur != i
				&& coord[i - 1].x == coord[line->used + 1].x - 1)
			ft_putchar('\n');
	}
	line->cur = sh_move_cur(i, line->pos, coord, tc);
}
