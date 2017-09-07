#include "shell.h"

int		sh_del_l(t_line *line, t_coord **coord, t_tc tc)
{
	if (!line->cur)
		return (0);
	line->cur = sh_move_cur(line->cur, line->cur - 1, *coord, tc);
	ft_memmove(line->str + line->cur, line->str + line->cur + 1,
			ft_strlen(line->str + line->cur + 1) + 1);
	line->used -= 1;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc.prompt)))
		return (-1);
	line->pos = line->cur;
	return (LEXER | DISP);
}

int		sh_del_r(t_line *line, t_coord **coord, t_tc tc)
{
	if (line->cur == line->used)
		return (0);
	ft_memmove(line->str + line->cur, line->str + line->cur + 1,
		ft_strlen(line->str + line->cur + 1) + 1);
	line->used -= 1;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc.prompt)))
		return (-1);
	line->pos = line->cur;
	return (LEXER | DISP);
}
