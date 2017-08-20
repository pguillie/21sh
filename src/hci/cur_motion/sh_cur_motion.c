#include "shell.h"

int		sh_cur_motion(long input, t_line *line, size_t *dest)
{
	if (input == K_RIGHT && line->str[line->cur])
		*dest = line->cur + 1;
	else if (input == K_LEFT && line->cur)
		*dest = line->cur - 1;
	else if (input == K_HOME)
		*dest = 0;
	else if (input == K_END)
		*dest = line->used;
	else
		return (0);
	return (1);
}
