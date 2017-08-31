#include "shell.h"

/*
**	RETURN STATUS:
**
**	-1	malloc error
**	lexer status
*/

static int	sh_end_of_line(t_line *line, t_coord **coord, t_tc tc)
{
	line->cur = sh_move_cur(line->cur, line->used, *coord, tc);
	if (sh_ins_char(line, tc, coord, '\n'))
		return (-1);
	return (1);
}

static int	sh_edit_key(t_line **line, t_coord **coord, t_tc tc)
{
	long	input;
	size_t	pos;

	input = key_input();
	if (input == '\n')
		return (sh_end_of_line(*line, coord, tc));
	else if (sh_cur_motion(input, *line, &pos, *coord))
		(*line)->cur = sh_move_cur((*line)->cur, pos, *coord, tc);
	else if ((input == K_DEL_L && (*line)->cur) || (input == K_DEL_R &&
				(*line)->str[(*line)->cur]))
		return (sh_del_char(*line, tc, coord, input));
	else if (input >= ' ' && input < 127)
		return (sh_ins_char(*line, tc, coord, input));
	else if (((input == K_UP || input == K_P_UP) && (*line)->up) ||
			((input == K_DOWN || input == K_P_DOWN) && (*line)->down))
		return (sh_edit_hist(line, input, coord, tc));
	return (0);
}

static int	sh_coord_del(t_coord **coord)
{
	if (*coord)
		ft_memdel((void**)coord);
	return (-1);
}

int			sh_edit_line(t_line **line, char **save, t_token **lexer, t_tc tc)
{
	t_coord	*coord;
	char	*full;
	int		success[2];

	if (!(coord = sh_create_coord(*line, tc.prompt)))
		return (-1);
	if (sh_lexer(*save ? *save : "", lexer) < 0)
		return (sh_coord_del(&coord));
	full = NULL;
	success[0] = 0;
	while (!success[0])
	{
		if ((success[0] = sh_edit_key(line, &coord, tc)) < 0)
			return (sh_coord_del(&coord));
		full ? ft_strdel(&full) : 0;
		full = ft_strjoin(*save, (*line)->str);
		if (!full || (success[1] = sh_lexer(full, lexer)) < 0)
			return (sh_coord_del(&coord));
	}
	free(coord);
	*save ? ft_strdel(save) : 0;
	*save = full;
	return (success[1]);
}
