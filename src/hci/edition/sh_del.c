#include "shell.h"

void	sh_del_afcur(t_line *line, t_tc tc, t_coord *coord)
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
			ft_putstr("\n");
			tputs(tc.cd, 0, termput);
			last = line->cur + browse;
		}
		browse++;
	}
	sh_move_cur(last, line->cur, coord, tc);
}

int		sh_del_char(t_line *line, t_tc tc, t_coord **coord, long input)
{
	if (input == K_DEL_L)
		line->cur = sh_move_cur(line->cur, line->cur - 1, *coord, tc);
	ft_memmove(line->str + line->cur, line->str + line->cur + 1,
			ft_strlen(line->str + line->cur));
	sh_del_afcur(line, tc, *coord);
	line->used -= 1;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc.prompt)))
		return (-1);
	sh_disp_line(line, *coord, tc);
	return (0);
}
