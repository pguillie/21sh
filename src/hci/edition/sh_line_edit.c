#include "shell.h"

//secu sur ins

int		sh_line_edit(t_line **line, t_tc tc)
{
	t_coord	*coord;
	long	input;
	size_t	pos;

	coord = sh_create_coord(*line, tc.prompt);//secu
	while ((input = key_input()) != '\n')
	{
		//if (input == K_UP || input == K_P_UP || input == K_DOWN || input == K_P_DOWN)////
		//	ft_printf("hist: %d\n", input);/////
		if (sh_cur_motion(input, *line, &pos, coord))
			(*line)->cur = sh_move_cur((*line)->cur, pos, coord, tc);
		else if ((input == K_DEL_L && (*line)->cur) || (input == K_DEL_R &&
			(*line)->str[(*line)->cur]))
			sh_del_char(*line, tc, &coord, input);
		else if (input >= ' ' && input < 127)
			sh_ins_char(*line, tc, &coord, input);
		else if (((input == K_UP || input == K_P_UP) && (*line)->prev) ||
				((input == K_DOWN || input == K_P_DOWN) && (*line)->next))
		{
			ft_printf("HISTORY\n");
			*line = sh_line_hist(*line, (input == K_UP || input == K_P_UP) ?
					(*line)->prev : (*line)->next, &coord, tc);
		}
	}
	sh_ins_char(*line, tc, &coord, '\n');
	return (0);
}
