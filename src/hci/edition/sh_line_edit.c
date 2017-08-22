#include "shell.h"

//secu
/*
void dispcoord(t_coord *c, int len)
{
	int i = 0;
	while (i < len)
	{
		printf("(%d;%d)\n", c[i].x, c[i].y);
		i++;
	}
}
*/
int		sh_line_edit(t_line *line, t_tc tc)
{
	t_coord	*coord;
	long	input;
	size_t	pos;

	while ((input = key_input()) != '\n')
	{
		coord = sh_create_coord(line, tc.prompt);//secu
	//	dispcoord(coord, line->used + 1);
		if (sh_cur_motion(input, line, &pos))
			line->cur = sh_move_cur(line->cur, pos, coord, tc);
		else if ((input == K_DEL_L && line->cur) || (input == K_DEL_R && line->str[line->cur]))
			sh_del_char(line, tc, coord, input);
		else if (input >= ' ' && input < 127)
			sh_ins_char(line, tc, coord, input);
		else if ((input == K_UP && line->prev) || (input == K_DOWN && line->next))
			line = sh_line_hist(line, input == K_UP ? line->prev : line->next, coord, tc);
	}
	sh_ins_char(line, tc, coord, '\n');
	return (0);
}
