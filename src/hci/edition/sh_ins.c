#include "shell.h"

int		sh_ins_char(t_line *line, t_tc tc, t_coord **coord, char c)
{
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
	line->used += 1;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc.prompt)))
		return (-1);
	sh_disp_line(line, *coord, tc);
	line->cur = sh_move_cur(line->cur, line->cur + 1, *coord, tc);
	return (0);
}
