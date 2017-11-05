#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static char	*s = NULL;
	char		b[BUFF_SIZE + 1];
	size_t		i;
	int			c;

	if (!line || fd < 0 || !((c = BUFF_SIZE) > 0))
		return (-1);
	while (!ft_strchr(s, '\n') && c == BUFF_SIZE)
	{
		ft_bzero(b, BUFF_SIZE + 1);
		c = read(fd, b, BUFF_SIZE);
		(s = ft_strappend(s, b)) && c < 0 ? ft_strdel(&s) : 0;
		if (!s)
			return (-1);
	}
	i = 0;
	while (!(*line = NULL) && s[i] && s[i] != '\n')
		i++;
	s[i] && !(*line = ft_strndup(s, i)) ? ft_strdel(&s) : 0;
	if (!s)
		return (-1);
	ft_memmove(s, s + i + (s[i] ? 1 : 0),
		ft_strlen(s + i + (s[i] ? 1 : 0)) + 1);
	s[0] == 0 ? ft_strdel(&s) : 0;
	return (c == BUFF_SIZE || s || *line ? 1 : 0);
}
