#include "shell.h"

t_coord		*sh_create_coord(t_line *line, size_t prompt)
{
	struct winsize	w;
	t_coord 		*new;
	t_coord			cur;
	size_t			i;

	if (ioctl(0, TIOCGWINSZ, &w) < 0)
		return (NULL);
	if (!(new = (t_coord*)ft_memalloc(sizeof(t_coord) * (line->used + 2))))
		return (NULL);
	i = 0;
	cur.x = 0;
	cur.y = 0;
	while (i < prompt)
	{
		if (++cur.x == w.ws_col)
		{
			cur.x = 0;
			cur.y += 1;
		}
		i++;
	}
	i = 0;
	while (i <= line->used)
	{
		new[i].x = cur.x;
		new[i].y = cur.y;
		if (++cur.x == w.ws_col || line->str[i] == '\n')
		{
			cur.x = 0;
			cur.y += 1;
		}
		i++;
	}
	new[i].x = w.ws_col;
	new[i].y = w.ws_row;
	return (new);
}
