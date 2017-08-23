#include "shell.h"

void	sh_del_after(t_line *line, t_tc tc, t_coord *coord)
{
	size_t	last;
	size_t	browse;

	tputs(tc.ce, 0, termput);
	last = line->cur;
	browse = 1;
	while (line->cur + browse < line->used)
	{
		if (coord[line->cur + browse].x == 0)
		{
			ft_putstr("\n\r");
			tputs(tc.cd, 0, termput);
			last = line->cur + browse;
		}
		browse++;
	}
	sh_move_cur(last, line->cur, coord, tc);
}

void    sh_del_char(t_line *line, t_tc tc, t_coord **coord, long value)
{
	if (value == K_DEL_L)
		line->cur = sh_move_cur(line->cur, line->cur - 1, *coord, tc);
	ft_memmove(line->str + line->cur, line->str + line->cur + 1,
			ft_strlen(line->str + line->cur));
	sh_del_after(line, tc, *coord);
	ft_putstr(line->str + line->cur);
	line->used -= 1;
	free(*coord);
	*coord = sh_create_coord(line, tc.prompt);
	line->cur = sh_move_cur(line->used, line->cur, *coord, tc);
}
