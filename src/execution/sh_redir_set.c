#include "shell.h"

static int	sh_redir_fd(t_redir red, int *fd)
{
	int		i;
	int		spec;

	i = -1;
	spec = 0;
	while (red.right[++i])
		if (!ft_isdigit(red.right[i])
				&& (red.right[i] != '-' || red.right[i + 1]))
			spec = 1;
	if (spec && (red.right[i - 1] == '-' || red.left != 1))
		return (RDR_AMBG);
	else if (spec)
	{
		*fd = open(red.right, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		return (1);
	}
	else
	{
		if ((*fd = dup(ft_atoi(red.right))) < 0)
			return (RDR_BADFD + (*fd = 0));
		if (red.right[i - 1] == '-')
			close(red.left);
	}
	return (0);
}

static int	sh_redir_here(t_redir red, int *fd)
{
	int		pfd[2];

	if (pipe(pfd) < 0)
		return (RDR_PIPE);
	if (ft_strequ(red.type, "<<"))
		ft_putstr_fd(red.right, pfd[1]);
	else
		ft_putendl_fd(red.right, pfd[1]);
	*fd = pfd[0];
	close(pfd[1]);
	return (0);
}

static int	sh_redir_open(t_redir red, int *fd)
{
	int		ret;

	ret = 0;
	if (ft_strequ(red.type, ">&") || ft_strequ(red.type, "<&"))
		ret = sh_redir_fd(red, fd);
	else if (ft_strequ(red.type, ">"))
		*fd = open(red.right, O_CREAT | O_WRONLY | O_TRUNC,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (ft_strequ(red.type, ">>"))
		*fd = open(red.right, O_CREAT | O_WRONLY | O_APPEND,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (ft_strequ(red.type, "<<") || ft_strequ(red.type, "<<<"))
		ret = sh_redir_here(red, fd);
	else
		*fd = open(red.right, O_RDONLY);
	if (ret)
		return (ret);
	if (*fd < 0)
		return (access(red.right, F_OK) ? RDR_NOENT : RDR_NORGHT);
	return (0);
}

static int	sh_redir_msg(int msg, char *file)
{
	if (msg == RDR_AMBG)
		ft_error(SHELL, file, "Ambiguous redirect");
	else if (msg == RDR_BADFD)
		ft_error(SHELL, file, "Bad file descriptor");
	else if (msg == RDR_NOENT)
		ft_error(SHELL, file, E_NOENT);
	else if (msg == RDR_NORGHT)
		ft_error(SHELL, file, E_NORGHT);
	else if (msg == RDR_PIPE)
	{
		ft_error(SHELL, "Failed to redirect stream", NULL);
		return (-1);
	}
	return (1);
}

int			sh_redir_set(t_redir *redir, int fd[10])
{
	int		i;
	int		ret;
	char	*file;

	i = 0;
	file = NULL;
	while (redir[i].type)
	{
		if (fd[redir[i].left] != -1)
			close(fd[redir[i].left]);
		fd[redir[i].left] = 0;
		if ((ret = sh_redir_open(redir[i], fd + redir[i].left)) < 0)
			return (sh_redir_msg(ret, redir[i].right));
		if (dup2(fd[redir[i].left], redir[i].left) < 0)
			return (-1);
		if (ret && dup2(1, 2) < 0)
			return (-1);
		i++;
	}
	return (0);
}
