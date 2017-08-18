#include "shell.h"

int		sh_line_edit(t_line *line, t_tc tc)
{
	long	value;

	while ((value = key_input()) != '\n')
	{
		if ((value == K_DEL_L && line->cur) || (value == K_DEL_R && line->str[line->cur]))
			sh_del_char(line, tc, value);
		else if (value >= ' ' && value < 127)
			sh_ins_char(line, tc, value);
		else if ((value == K_LEFT && line->cur) || (value == K_RIGHT && line->str[line->cur]))
			line->cur = sh_cur_motion(line->cur, value == K_LEFT ? line->cur - 1 : line->cur + 1, tc);
		else if (value == K_HOME || value == K_END)
			line->cur = sh_cur_motion(line->cur, value == K_HOME ? 0 : line->used, tc);
		else if ((value == K_UP && line->prev) || (value == K_DOWN && line->next))
			line = sh_line_hist(line, value == K_UP ? line->prev : line->next, tc);
	}
	sh_ins_char(line, tc, '\n');
	return (0);
}
