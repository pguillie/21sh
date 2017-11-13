#include "shell.h"

int		sh_tab_ins(t_line *line, t_coord **coord, t_tc tc, char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (line->used + len >= line->capacity)
	{
		line->capacity += BUFF_SIZE * ((len / BUFF_SIZE) + 1);
		if (!(line->str = (char*)ft_realloc(line->str, line->used,
						line->capacity, sizeof(char))))
			return (-1);
	}
	ft_memmove(line->str + line->cur + len, line->str + line->cur,
			ft_strlen(line->str + line->cur));
	ft_strncpy(line->str + line->cur, s, len);
	line->used += len;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc.prompt)))
		return (-1);
	line->pos = line->cur + len;
	return (LEXER | DISP);
}
