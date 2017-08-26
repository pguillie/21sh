#include "shell.h"

/*
**	Pour tous les deplacements + SHIFT (selection):
**		1) mettre un boolen `selection' sur `true'
**		2) faire le mouvement normal
**		3) gerer la selection
*/

int		sh_cur_motion(long input, t_line *line, size_t *dest, t_coord *coord)
{
	int		ret;

	ret = 1;
	if (input == K_RIGHT && line->str[line->cur])
		*dest = line->cur + 1;
	else if (input == K_LEFT && line->cur)
		*dest = line->cur - 1;
	else if (input == K_C_RIGHT || input == K_C_LEFT)
		*dest = sh_move_word(input, line);
	else if (input == K_UP || input == K_DOWN)
		*dest = sh_move_line(input, coord, line, &ret);
	else if (input == K_HOME)
		*dest = 0;
	else if (input == K_END)
		*dest = line->used;
	else
		return (0);
	return (ret);
}
