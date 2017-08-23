#include "shell.h"

int		sh_ins_char(t_line *line, t_tc tc, t_coord *coord, char c)
{
	struct winsize	w;

	if (ioctl(0, TIOCGWINSZ, &w) < 0)
		return (1);
	if (line->used == line->capacity - 1)
	{
		line->capacity += BUFF_SIZE;
		if (!(line->str = ft_realloc(line->str, line->used,
				line->capacity, sizeof(char))))
			return (-1);
	}
	ft_memmove(line->str + line->cur + 1, line->str + line->cur,
			ft_strlen(line->str + line->cur));
	line->str[line->cur] = c;
	ft_putstr(line->str + line->cur);
	line->used += 1;
	(line->used + tc.prompt) % w.ws_col == 0 ? ft_putstr("\n") : 1;
	coord = sh_create_coord(line, tc.prompt);
	line->cur = sh_move_cur(line->used, line->cur + 1, coord, tc);
	return (0);
}
