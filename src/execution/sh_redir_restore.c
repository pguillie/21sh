#include "shell.h"

int			sh_redir_backup(int std[3])
{
	std[0] = dup(0);
	std[1] = dup(1);
	std[2] = dup(2);
	return (0);
}

int			sh_redir_restore(int fd[10], int std[3])
{
	int				i;

	i = 0;
	while (fd[i])
	{
		if (fd[i] > -1)
			close(fd[i]);
		i++;
	}
	dup2(std[0], 0);
	dup2(std[1], 1);
	dup2(std[2], 2);
	return (0);
}
