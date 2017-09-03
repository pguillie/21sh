#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static char	*s[512] = {NULL};
	char		b[BUFF_SIZE + 1];
	size_t		i;
	int			c;
	
	if (!line || fd < 0 || fd >= 512 || !((c = BUFF_SIZE) > 0))
		return (-1);
	while (!ft_strchr(s[fd], '\n') && c == BUFF_SIZE)
	{
		ft_bzero(b, BUFF_SIZE + 1);
		c = read(fd, b, BUFF_SIZE);
		(s[fd] = ft_strappend(s[fd], b)) && c < 0 ? ft_strdel(&s[fd]) : 0;
		if (!s[fd])
			return (-1);
	}
	i = 0;
	while (!(*line = NULL) && s[fd][i] && s[fd][i] != '\n')
		i++;
	s[fd][i] && !(*line = ft_strndup(s[fd], i)) ? ft_strdel(&s[fd]) : 0;
	if (!s[fd])
		return (-1);
	ft_memmove(s[fd], s[fd] + i + (s[fd][i] ? 1 : 0),
		ft_strlen(s[fd] + i + (s[fd][i] ? 1 : 0)) + 1);
	s[fd][0] == 0 ? ft_strdel(&s[fd]) : 0;
	return (c == BUFF_SIZE || s[fd] || *line ? 1 : 0);
}
