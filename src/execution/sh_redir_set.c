#include "shell.h"

static int	sh_red_here(t_redir red, int fd[10])
{
	int		pfd[2];

	if (pipe(pfd) < 0)
		return (1);
	if (ft_strlen(red.type) == 2)
		ft_putstr_fd(red.right, pfd[1]);
	else
		ft_putendl_fd(red.right, pfd[1]);
	close(pfd[1]);
	fd[red.left] = pfd[0];
	if (dup2(fd[red.left], red.left) < 0)
		return (1);
	return (0);
}

static int	sh_red_both(t_redir red, int *fd)
{
	if (red.type[0] == '<' || red.left != 1)
		return (ft_error(SHELL, red.right, "Ambigous redirect"));
	else if ((*fd = open(red.right, O_WRONLY | O_TRUNC | O_CREAT,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < -1)
		return (ft_error(SHELL, red.right, access(red.right, F_OK) ?
					E_NOENT : E_NORGHT));
	else if (dup2(*fd, 1) < 0 || dup2(1, 2) < 0)
		return (1);
	return (0);
}

static int	sh_red_amersand(t_redir red, int fd[10])
{
	int		i;
	int		dig_wor;

	dig_wor = red.type[0] == '&' ? 1 : 0;
	i = 0;
	while (red.right[i + 1])
		if (!ft_isdigit(red.right[i++]))
			dig_wor = 1;
	if (i == 0 && red.right[i] == '-')
		close(red.left);
	else if (dig_wor == 0 && (ft_isdigit(red.right[i]) || red.right[i] == '-'))
	{
		fd[red.left] = ft_atoi(red.right);
		if (dup2(fd[red.left], red.left) < 0)
			return (ft_error(SHELL, red.right, E_BADFD));
		if (red.right[i] == '-')
		{
			close(fd[red.left]);
			fd[red.left] = -1;
		}
	}
	else
		return (sh_red_both(red, fd + 1));
	return (0);
}

static int	sh_red_simple(t_redir red, int fd[10])
{
	if (ft_strequ(red.type, ">"))
		fd[red.left] = open(red.right, O_WRONLY | O_TRUNC | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (ft_strequ(red.type, ">>"))
		fd[red.left] = open(red.right, O_WRONLY | O_APPEND | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (ft_strequ(red.type, "<"))
		fd[red.left] = open(red.right, O_RDONLY);
	else if (ft_strequ(red.type, "<>"))
		fd[red.left] = open(red.right, O_RDWR | O_CREAT,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd[red.left] < 0)
	{
		return (ft_error(SHELL, red.right, access(red.right, F_OK) ?
						E_NOENT : E_NORGHT));
	}
	dup2(fd[red.left], red.left);
	return (0);
}

int			sh_redir_set(t_redir *redir, int fd[10])
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (redir[i].type)
	{
		if (fd[redir[i].left] > -1)
		{
			close(fd[redir[i].left]);
			fd[redir[i].left] = -1;
		}
		if (ft_strstr(redir[i].type, "<<"))
			ret = sh_red_here(redir[i], fd);
		else if (ft_strchr(redir[i].type, '&'))
			ret = sh_red_amersand(redir[i], fd);
		else
			ret = sh_red_simple(redir[i], fd);
		if (ret)
			return (ret);
		i++;
	}
	return (0);
}
