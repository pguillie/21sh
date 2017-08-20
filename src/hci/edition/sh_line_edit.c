#include "shell.h"

//secu

int		sh_line_edit(t_line *line, int prompt, t_tc tc)
{
	long	input;
	size_t	pos;

	while ((input = key_input()) != '\n')
	{
		if (sh_cur_motion(input, line, &pos))
			line->cur = sh_move_cur(line->cur, pos, tc);
		else if ((input == K_DEL_L && line->cur) || (input == K_DEL_R && line->str[line->cur]))
			sh_del_char(line, tc, input);
		else if (input >= ' ' && input < 127)
			sh_ins_char(line, tc, input);
		else if ((input == K_UP && line->prev) || (input == K_DOWN && line->next))
			line = sh_line_hist(line, input == K_UP ? line->prev : line->next, tc);
	}
	sh_ins_char(line, tc, '\n');
	return (0);
}
