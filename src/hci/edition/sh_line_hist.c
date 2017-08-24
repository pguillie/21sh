#include "shell.h"

t_line	*sh_line_hist(t_line *line, t_line *new, t_coord **coord, t_tc tc)
{
	struct winsize	w;

	if (ioctl(0, TIOCGWINSZ, &w) < 0)
		return (NULL);
	line->cur = sh_move_cur(line->cur, 0, *coord, tc);
	sh_del_after(line, tc, *coord);
	line = new;
	(line->used + tc.prompt) % w.ws_col == 0 ? ft_putstr("\n") : 1;
	ft_putstr(line->str);
	free(*coord);
	*coord = sh_create_coord(line, tc.prompt);
	line->cur = line->used;
	return (line);
}
