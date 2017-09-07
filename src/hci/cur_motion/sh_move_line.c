#include "shell.h"

int		sh_move_line(int move, t_line *line, t_coord *coord)
{
	size_t	i;

	(void)move;
	(void)coord;
	i = line->cur;
//	while (1)//
//		;//
	return (0);//
}
/*
size_t	sh_move_line(long input, t_coord *coord, t_line *line, int *ret)
{
	size_t	i;
	size_t	end;

	i = 0;
	if ((input == K_UP && coord[line->cur].y == coord[0].y)
			|| (input == K_DOWN && coord[line->cur].y == coord[line->used].y))
	{
		*ret = 0;
		return (0);
	}
	*ret = 1;
	while (coord[i].y != coord[line->cur].y - (input == K_UP ? 1 : -1))
		i++;
	end = i;
	while (coord[end].y == coord[line->cur].y - (input == K_UP ? 1 : -1))
		end++;
	if (line->str[end - 1] == '\n' && (!coord[i].y || !coord[line->cur].y))
		while (i < end - 1 && coord[i].x < coord[line->cur].x
				+ coord[0].x * (coord[i].y ? -1 : 1))
			i++;
	else
		while (i < end - 1 && coord[i].x < coord[line->cur].x)
			i++;
	return (i);
}*/
