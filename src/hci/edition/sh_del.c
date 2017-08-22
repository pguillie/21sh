#include "shell.h"

void    sh_del_char(t_line *line, t_tc tc, t_coord *coord, long value)
{
	if (value == K_DEL_L)
		line->cur = sh_move_cur(line->cur, line->cur - 1, coord, tc);
	ft_memmove(line->str + line->cur, line->str + line->cur + 1,
			ft_strlen(line->str + line->cur));
	ft_putstr(line->str + line->cur);
	tputs(tc.dc, 0, termput);
	line->used -= 1;
	coord = sh_create_coord(line, tc.prompt);
	line->cur = sh_move_cur(line->used, line->cur, coord, tc);
}
