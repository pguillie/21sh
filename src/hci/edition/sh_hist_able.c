#include "shell.h"

static int	sh_convert_hist(char *esc)
{
	if (esc[1] == '[' && (esc[2] == 'A' || esc[2] == 'B'))
		return ((esc[2] ^ 64) | 4);
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
	if (id && !(id & 4))//define SEARCH_HIST 4
	{
		dprintf(5, "REINIT !\n");
		line->hist = -1;
	}
	else if (id && line->hist < 0)
	{
		dprintf(5, "INIT !\n");
		line->hist = line->cur;
	}
	dprintf(5, "hist: %d\n", line->hist);
	if (id & UP)
	{
		target = line->up;
		while (target && !ft_strnequ(line->str, target->str, line->hist))
			target = target->up;
	}
	else if (id & DOWN)
	{
		target = line->down;
		while (target && !ft_strnequ(line->str, target->str, line->hist))
			target = target->down;
	}
	return (target);
}
