#include "shell.h"

void    sh_del_char(t_line *line, t_tc tc, long value)
{
	if (value == K_DEL_L)
		line->cur = sh_cur_motion(line->cur, line->cur - 1, tc);
	ft_memmove(line->str + line->cur, line->str + line->cur + 1,
			ft_strlen(line->str + line->cur));
	ft_putstr(line->str + line->cur);
	tputs(tc.dc, 0, termput);
	line->cur = sh_cur_motion(--line->used, line->cur, tc);
}
