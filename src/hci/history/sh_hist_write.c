#include "shell.h"

int		sh_hist_write(char *line, char *last)
{
	char	*hist;
	int		fd;
	int		i;

	hist = ft_strcjoin(getenv("HOME"), HIST_FILE, '/');
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] && !ft_strequ(line, last))
	{
		if ((fd = open(hist ? hist : HIST_FILE, O_WRONLY | O_APPEND | O_CREAT,
						S_IRUSR | S_IWUSR)) < 0)
		{
			ft_strdel(&hist);
			return (1);
		}
		write(fd, line, ft_strlen(line));
		close(fd);
	}
	ft_strdel(&hist);
	return (0);
}
