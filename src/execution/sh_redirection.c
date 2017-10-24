#include "shell.h"

static int	sh_redir_open(t_redir red)
{
	int		fd;

	if (ft_strequ(red.type, ">&") || ft_strequ(red.type, "<&"))
		fd = dup(ft_atoi(red.right));
	else if (ft_strequ(red.type, ">"))
		fd = open(red.right, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (ft_strequ(red.type, ">>"))
		fd = open(red.right, O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(red.right, O_RDONLY);
	return (fd);
}

int			sh_redir_backup(int std[3])
{
	std[0] = dup(0);
	std[1] = dup(1);
	std[2] = dup(2);
	return (0);
}

int			sh_redir_set(t_redir *redir, int fd[10])
{
	int i;

	i = 0;
	while (redir[i].type)
	{
		if (fd[redir[i].left] != -1)
			close(fd[redir[i].left]);
		fd[redir[i].left] = sh_redir_open(redir[i]);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (fd[i] > -1)
			dup2(fd[i], i);
		i++;
	}
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
