#include "shell.h"

t_coord		*sh_create_coord(t_line *line, int prompt)
{
	struct winsize	w;
	t_coord 		*new;
	t_coord			cur;
	size_t			i;
	int		fd;
	fd = open("./test2", O_WRONLY | O_APPEND | O_CREAT,
					S_IRUSR | S_IWUSR);

	if (ioctl(0, TIOCGWINSZ, &w) < 0)
		return (NULL);
	if (!(new = (t_coord*)ft_memalloc(sizeof(t_coord) * line->used)))
		return (NULL);
	i = 0;
	cur.x = prompt;
	cur.y = 0;
	dprintf(fd, "\n" );
	while (i <= line->used)
	{
		new[i].x = cur.x;
		new[i].y = cur.y;
		if (++cur.x == w.ws_col || line->str[i] == '\n')
		{
			cur.x = 0;
			cur.y += 1;
		}
		dprintf(fd, "%d;%d\n", new[i].x,new[i].y);
		i++;
	}
	return (new);
}
