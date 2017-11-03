#include "shell.h"

int		sh_paste(t_line *line, t_coord **coord, t_tc *tc)
{
	size_t	len;

	if (!tc->clipboard)
		return (0);
	len = ft_strlen(tc->clipboard);
	if (line->used + ft_strlen(tc->clipboard) >= line->capacity)
	{
		line->capacity += BUFF_SIZE * ((len / BUFF_SIZE) + 1);
		if (!(line->str = ft_realloc(line->str, line->used,
						line->capacity, sizeof(char))))
			return (-1);
	}
	ft_memmove(line->str + line->cur + len, line->str + line->cur,
			ft_strlen(line->str + line->cur));
	ft_strncpy(line->str + line->cur, tc->clipboard, len);
	line->used += len;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc->prompt)))
		return (-1);
	line->pos = line->cur + ft_strlen(tc->clipboard);
	return (DISP | LEXER);
}
