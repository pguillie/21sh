#include "shell.h"

static int	sh_tree_cmd(t_tree *root, int ret)
{
	extern char	**environ;
	int			fd[10];
	int			std[3];
	int			red_ret;

	memset(fd, -1, sizeof(int) * 10);
	sh_redir_backup(std);
	if (!(red_ret = sh_redir_set(root->cmd->redir, fd)))
		ret = sh_av_pipe(root->cmd->av, environ, ret);
	sh_redir_restore(fd, std);
	return (red_ret ? red_ret : ret);
}

int			sh_tree_browse(t_tree *root, int ret)
{
	if (root)
	{
		if (root->cmd)
			ret = sh_tree_cmd(root, ret);
		else if (root->op)
		{
			ret = sh_tree_browse(root->left, ret);
			if (!(ft_strequ(root->op, "&&") && ret)
					&& !(ft_strequ(root->op, "||") && !ret) && root->right)
				ret = sh_tree_browse(root->right, ret);
		}
	}
	return (ret);
}
