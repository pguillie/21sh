#include "shell.h"

int		sh_paste(t_line *line, t_coord **coord, t_tc *tc)
{
	size_t	i;

	if (!tc->clipboard)
		return (0);
	i = ft_strlen(tc->clipboard) + 1;
	if (line->used + ft_strlen(tc->clipboard) >= line->capacity)
	{
		line->capacity += ((line->used + i)
				/ BUFF_SIZE + 1) * BUFF_SIZE;
		if (!(line->str = ft_realloc(line->str, line->used,
						line->capacity, sizeof(char))))
			return (-1);
	}
	ft_memmove(line->str + line->cur + i - 1,
			line->str + line->cur,
			ft_strlen(line->str + line->cur));
	ft_strncpy(line->str + line->cur, tc->clipboard, i - 1);
	line->used += i - 1;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc->prompt)))
		return (-1);
	line->pos = line->cur + ft_strlen(tc->clipboard);
	return (DISP | LEXER);
}
