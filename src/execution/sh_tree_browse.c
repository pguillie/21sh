#include "shell.h"

static int	sh_pipe_left(t_tree *root, int pipe_out)
{
	int		std[3];
	int		ret;

	if (sh_redir_init(std, 0, 1, 1))
		exit(-1);
	if (dup2(pipe_out, 1) < 0
			|| (ft_strequ(root->op, "|&") && dup2(pipe_out, 2) < 0))
		exit(sh_redir_restore(std, 0, 1, 1) - 1);
	ret = sh_tree_browse(root->left);
	close(pipe_out);
	if (sh_redir_restore(std, 0, 1, 1) < 0)
		ret = -1;
	exit(ret);
}

static int	sh_pipe_right(t_tree *root, int pipe_in)
{
	int		stdin;
	int		ret;

	if ((stdin = dup(0)) < 0 || dup2(pipe_in, 0) < 0)
		return (-1);
	ret = sh_tree_browse(root->right);
	close(pipe_in);
	if (dup2(stdin, 0) < 0)
		ret = -1;
	return (ret);
}

static int	sh_pipe(t_tree *root)
{
	pid_t	child;
	int		fildes[2];
	int		ret;

	ft_printf("pipe\n");
	if (pipe(fildes) < 0)
		return (-1);
	if ((child = fork()) < 0)
		return (-1);
	if (child == 0)
	{
		close(fildes[0]);
		exit(sh_pipe_left(root, fildes[1]));
	}
	else
	{
		waitpid(child, &ret, 0);
		close(fildes[1]);
		ret = sh_pipe_right(root, fildes[0]);
	}
	return (ret);
}

int			sh_tree_browse(t_tree *root)
{
	int ret;

	if (!root || (ft_strequ(root->op, "\n") && !(root->left)))
		return (0);
	ret = -1;
	if (root->cmd)
	{
//		sh_redir_set(root->cmd->redir, root->cmd->nb_redir, int back[]);
		ret = sh_execution(root->cmd->av);
//		sh_redir_res(back);
	}
	else if (root->op)
	{
		if (ft_strequ(root->op, "|") || ft_strequ(root->op, "|&"))
			ret = sh_pipe(root);
		else
		{
			if (root->left)
				ret = sh_tree_browse(root->left);
			if (!(ft_strequ(root->op, "&&") && ret)
					&& !(ft_strequ(root->op, "||") && !ret) && root->right)
				ret = sh_tree_browse(root->right);
		}
	}
	return (ret);
}
