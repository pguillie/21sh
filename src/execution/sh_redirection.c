#include "shell.h"

static int	sh_open_redir(char *type, char *right)
{
	int fd;

	fd = 0;
	if (ft_strequ(type, ">&") || ft_strequ(type, "<&"))
		fd = dup(ft_atoi(right));
	if (ft_strequ(type, ">"))
		if ((fd = open(right, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (-1);
	if (ft_strequ(type, ">>"))
		if ((fd = open(right, O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (-1);
	if (ft_strequ(type, "<"))
		if ((fd = open(right, O_RDONLY,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
			return (-1);
	return (fd);
}

int			sh_redir_set(t_redir *redir, int std[], int *fd)
{
	int		i;

	i = 0;
	*fd = 0;
	while (redir[i].type)
	{
		*fd ? close(*fd) : 0;
		if ((*fd = sh_open_redir(redir[i].type, redir[i].right)) < 0)
			return (ft_error(E_NOENT, redir[i].right, NULL));
		if (redir[i].left < 3 && std[redir[i].left] < 0)
			std[redir[i].left] = dup(redir[i].left);
		dup2(*fd, redir[i].left);
		i++;
	}
	return (0);
}

void		sh_redir_restore(int std[], int fd)
{
	int		i;

	i = 0;
	dup2(std[0], 0);
	dup2(std[1], 1);
	dup2(std[2], 2);
	if (dup(std[0]) >= 0)
		close(std[0]);
	if (dup(std[1]) >= 0)
		close(std[1]);
	if (dup(std[2]) >= 0)
		close(std[2]);
	if (fd > 2)
		close(fd);
}
