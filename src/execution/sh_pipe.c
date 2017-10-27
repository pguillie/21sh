#include "shell.h"

static int	sh_pipe_left(char *av[], int pipe_out, char *env[], int ret)
{
	int		stdout;

	stdout = dup(1);
	dup2(pipe_out, 1);
	ret = sh_av_pipe(av, env, ret);
	close(pipe_out);
	dup2(stdout, 1);
	return (ret);
}

static int	sh_pipe_right(char *av[], int pipe_in, char *env[], int ret)
{
	int		stdin;

	stdin = dup(0);
	dup2(pipe_in, 0);
	ret = sh_av_pipe(av, env, ret);
	close(pipe_in);
	dup2(stdin, 0);
	return (ret);
}

static int	sh_pipe(char *avl[], char *avr[], char *env[], int ret)
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
		exit(sh_pipe_left(avl, fildes[1], env, ret));
	}
	else
	{
		close(fildes[1]);
		waitpid(child, &ret, 0);
		ret = sh_pipe_right(avr, fildes[0], env, ret);
	}
	return (ret);
}

int			sh_av_pipe(char *av[], char *environ[], int ret)
{
	size_t	i;

	i = 0;
	while (av[i] && !ft_strequ(av[i], "|"))
		i++;
	if (!av[i])
		ret = sh_execution(av, environ, ret);
	else
	{
		free(av[i]);
		av[i] = NULL;
		ret = sh_pipe(av, av + i + 1, environ, ret);
		av[i] = ft_strdup("|");
	}
	return (ret);
}
