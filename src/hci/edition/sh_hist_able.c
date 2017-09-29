#include "shell.h"

static int	sh_convert_hist(char *esc)
{
	if (esc[1] == '[' && (esc[2] == 'A' || esc[2] == 'B'))
		return ((esc[2] ^ 64) | 4);
	else if (esc[1] == '[' && (esc[2] == '5' || esc[2] == '6') && esc[3] == '~')
		return (esc[2] ^ 52);
	return (0);
}

t_line		*sh_hist_able(char *esc, t_line *line, int *hist_search)
{
	t_line	*target;
	int		id;

	target = NULL;
	id = sh_convert_hist(esc);
	if (id & HIST_SEARCH)
	{
		*hist_search = 1;
		if (!line->h_smd)
		{
			line->h_smd = 1;
			line->h_pos = line->cur;
		}
	}
	else
		line->h_smd = 0;
	if (id & UP)
	{
		target = line->up;
		if (line->h_smd)
			while (target && (!ft_strnequ(line->str, target->str, line->h_pos)
						|| !ft_strcmp(line->str, target->str)))
				target = target->up;
	}
	else if (id & DOWN)
	{
		target = line->down;
		if (line->h_smd)
			while (target && (!ft_strnequ(line->str, target->str, line->h_pos)
						|| !ft_strcmp(line->str, target->str)))
				target = target->down;
	}
	return (target);
}
