#include "shell.h"

static int	sh_pipe_left(t_tree *root, int pipe_out, int ret)
{
	int		stdout;

	stdout = dup(1);
	dup2(pipe_out, 1);
	ret = sh_tree_browse(root->left, ret);
	close(pipe_out);
	dup2(stdout, 1);
	return (ret);
}

static int	sh_pipe_right(t_tree *root, int pipe_in, int ret)
{
	int		stdin;

	stdin = dup(0);
	dup2(pipe_in, 0);
	ret = sh_tree_browse(root->right, ret);
	close(pipe_in);
	dup2(stdin, 0);
	return (ret);
}

static int	sh_pipe(t_tree *root, int ret)
{
	pid_t	child;
	int		fildes[2];

	if (pipe(fildes) < 0)
		return (-1);
	if ((child = fork()) < 0)
		return (-1);
	if (child == 0)
	{
		close(fildes[0]);
		exit(sh_pipe_left(root, fildes[1], ret));
	}
	else
	{
		waitpid(child, &ret, 0);
		close(fildes[1]);
		ret = sh_pipe_right(root, fildes[0], ret);
	}
	return (ret);
}

static int	sh_tree_cmd(t_tree *root, int ret)
{
	extern char	**environ;
	int			fd[10];
	int			std[3];
	int			red_ret = 0;

	memset(fd, -1, sizeof(int) * 10);
	sh_redir_backup(std);
	if (!(red_ret = sh_redir_set(root->cmd->redir, fd)))
		ret = sh_execution(root->cmd->av, environ, ret);
	sh_redir_restore(fd, std);
	return (red_ret ? red_ret : ret);
	return (ret);
}

int			sh_tree_browse(t_tree *root, int ret)
{
	if (root)
	{
		if (root->cmd)
			ret = sh_tree_cmd(root, ret);
		if (root->op)
		{
			if (ft_strequ(root->op, "|"))
				ret = sh_pipe(root, ret);
			else
			{
				ret = sh_tree_browse(root->left, ret);
				if (!(ft_strequ(root->op, "&&") && ret)
						&& !(ft_strequ(root->op, "||") && !ret) && root->right)
					ret = sh_tree_browse(root->right, ret);
			}
		}
	}
	return (ret);
}
