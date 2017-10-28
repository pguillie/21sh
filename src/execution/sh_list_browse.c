#include "shell.h"

//pb de reinit fd

static int	sh_cmd(t_cmd *cmd, int ret)
{
	extern char	**environ;
	int			fd[10];
	int			std[3];

	sh_redir_backup(std);
	if (sh_redir_set(cmd->redir, fd))
	{
		sh_redir_restore(fd, std);
		return (-1);
	}
	ret = sh_execution(cmd->av, environ, ret);
	sh_redir_restore(fd, std);
	return (ret);
}

static int	sh_pipe(t_cmd **pipeline, int ret)
{
	pid_t	child;
	int		pfd[2];
	int		stdin;
	int		stdout;
	int		i;

	i = 0;
	while (pipeline[i])
		i++;
	if (i == 1)
		return (sh_cmd(pipeline[i - 1], ret));
	if (pipe(pfd) < 0 || (child = fork()) < 0)
		return (-1);
	if (child == 0)
	{
		close(pfd[0]);
		stdout = dup(1);
		dup2(pfd[1], 1);
		pipeline[i - 1] = NULL;//
		ret = sh_pipe(pipeline, ret);
		dup2(stdout, 1);
		close(pfd[1]);
		exit(ret);	
	}
	else
	{
		close(pfd[1]);
		stdin = dup(0);
		dup2(pfd[0], 0);
		ret = sh_cmd(pipeline[i - 1], ret);
		close(pfd[0]);
		dup2(stdin, 0);
	}
	return (ret);
}

int			sh_list_browse(t_cmd ***list, int *op, int ret)
{
	t_cmd	**pipeline;
	int		i;
	int		j;
	int		o;

	i = 0;
	j = 0;
	if (list)
	{
		while ((pipeline = list[i]))
		{
			if (!i || (!(o = op[j++]) || ((o > 0 && !ret) || (o < 0 && ret))))
				ret = sh_pipe(pipeline, ret);
			i++;
		}
	}
	return (ret);
}
