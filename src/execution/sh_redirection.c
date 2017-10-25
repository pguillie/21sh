#include "shell.h"

static int	sh_redir_fd(t_redir red)
{
	int		fd;
	int		i;
	int		ret;

	fd = -1;
	ret = 0;
	i = -1;
	while (red.right[++i])
		if (!ft_isdigit(red.right[i])
				&& (red.right[i] != '-' || red.right[i + 1]))
			ret++;
	if (ret && red.right[i - 1] == '-')
		return (RDR_AMB);
	else if (ret)
		fd = open(red.right, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
	{
		if ((fd = dup(ft_atoi(red.right))) < 0)
			return (RDR_BADFD);
		if (red.right[i - 1] == '-')
			close(ft_atoi(red.right));
	}
	return (fd);
}

static int	sh_redir_open(t_redir red)
{
	int		pfd[2];
	int		fd;

	if (ft_strequ(red.type, ">&") || ft_strequ(red.type, "<&"))
		fd = sh_redir_fd(red);
	else if (ft_strequ(red.type, ">"))
		fd = open(red.right, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (ft_strequ(red.type, ">>"))
		fd = open(red.right, O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (ft_strequ(red.type, "<<") || ft_strequ(red.type, "<<<"))
	{
		if (pipe(pfd) < 0)
			return (ft_error(SHELL, "Unable to set here-document or here-string", NULL) * -42);
		ft_putendl_fd(red.right, pfd[1]);
		fd = pfd[0];
		close(pfd[1]);
	}
	else
		fd = open(red.right, O_RDONLY);
	if (fd == -1)
	{
		ft_putendl("--- PB ---");
		if (fd & RDR_AMB)
			ft_error(SHELL, red.right, "Ambigous redirect");
		else if (fd & RDR_BADFD)
			ft_error(SHELL, red.right, "Bad fd");
		else
		ft_error(SHELL, red.right, access(red.right, F_OK) < 0 ?
				E_NOENT : E_NORGHT);
		return (-42);
	}
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
	int	ret;

	i = 0;
	while (redir[i].type)
	{
		if (fd[redir[i].left] != -1)
			close(fd[redir[i].left]);
		ret = sh_redir_open(redir[i]);
		if (ret < -1)
			return (-1);
		fd[redir[i].left] = ret;
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
