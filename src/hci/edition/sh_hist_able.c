#include "shell.h"

static int	sh_convert_hist(char *esc)
{
	if (esc[1] == '[' && (esc[2] == 'A' || esc[2] == 'B'))
		return (esc[2] ^ 64);
	else if (esc[1] == '[' && (esc[2] == '5' || esc[2] == '6') && esc[3] == '~')
		return (esc[2] ^ 52);
	return (0);
}

t_line		*sh_hist_able(char *esc, t_line *line)
{
	t_line	*target;
	int		id;

	target = NULL;
	id = sh_convert_hist(esc);
	if (id & UP && line->up)
		target = line->up;
	else if (id & DOWN && line->down)
		target = line->down;
	return (target);
}
