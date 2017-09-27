#include "shell.h"
int			sh_redir_set(t_redir *redir, int std[])
{
	int		fd;
	int		i;

	fd = 0;
	i = 0;
	ft_memset(std, -1, 10);
	while (redir[i].type)
	{
		if (ft_strequ(redir[i].type, ">&"))
			fd = ft_atoi(redir[i].right);
		if (ft_strequ(redir[i].type, "<&"))
			fd = ft_atoi(redir[i].right);
		if (ft_strequ(redir[i].type, ">"))
			fd = open(redir[i].right, O_CREAT | O_WRONLY | O_TRUNC,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (ft_strequ(redir[i].type, ">>"))
			fd = open(redir[i].right, O_CREAT | O_WRONLY | O_APPEND,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (ft_strequ(redir[i].type, "<"))
			if ((fd = open(redir[i].right, O_RDONLY,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
				return (ft_error(E_NOENT, redir[i].right, NULL));
		if (std[redir[i].left] < 0)
			std[redir[i].left] = dup(redir[i].left);
		dup2(fd, redir[i].left);
		i++;
	}
	return (0);
}

void		sh_redir_restore(int std[])
{
	int		i;

	i = 0;
	while (i < 10)
	{
		dup2(std[i], i);
		i++;
	}
}
