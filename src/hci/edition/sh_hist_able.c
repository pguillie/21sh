#include "shell.h"

static int	sh_convert_hist(char *esc)
{
	if (esc[1] == '[' && (esc[2] == 'A' || esc[2] == 'B'))
		return (1 << ((esc[2] ^ 64) - 1));
	else if (esc[1] == '[' && (esc[2] == '5' || esc[2] == '6') && esc[3] == '~')
		return (2 << (~esc[2] ^ 8));
return (0);
}

t_line		*sh_hist_able(char *esc, t_line *line)
{
	t_line	*target;
	int		id;

	id = sh_convert_hist(esc);
	if ((id & UP || id & P_UP) && line->up)
		target = line->up;
	else if ((id & DOWN || id & P_DO) && line->down)
		target = line->down;
	else
		return (line);
	return (target);
}
