#include "shell.h"

int		sh_del(t_line *line, t_coord **coord, t_tc tc)
{
	size_t	i;

	if (!line->cur)
		return (0);
	line->cur = sh_move_cur(line->cur, line->cur - 1, *coord, tc);
	ft_memmove(line->str + line->cur, line->str + line->cur + 1,
			ft_strlen(line->str + line->cur + 1) + 1);
	line->used -= 1;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc.prompt)))
		return (-1);
	tputs(tc.dc, 0, termput);
	i = line->cur;
	while (line->str[i] && line->str[i] != '\n')
	{
		if (line->str[i + 1] && (*coord)[i + 1].x == 0)
		{
			sh_move_cur(line->cur, i, *coord, tc);
			ft_putchar_fd(line->str[i + 1], 0);
			sh_move_cur(i, i + 1, *coord, tc);
			tputs(tc.dc, 0, termput);
			sh_move_cur(i + 1, line->cur, *coord, tc);
		}
		i++;
	}
	return (2);
}
