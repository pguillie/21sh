#include "shell.h"

static int		sh_sep_list(int category)
{
	if (category == ESPERCOLON || category == NEWLINE
			|| category == ANDOR)
		return (1);
	return (0);
}

static int		sh_count_lists(t_token *l)
{
	size_t	i;

	i = 0;
	while (l->next)
	{
		if (sh_sep_list(l->category))
			i++;
		l = l->next;
	}
	return (i + 1);
}

static int		sh_count_pipe(t_token *l)
{
	while (l->next && !sh_sep_list(l->category))
	{
		if (l->category == PIPE)
			i++;
		l = l->next;
	}
	return (i + 1);
}

static t_token	*sh_get_cmd(t_cmd ***list, t_token *l)
{
	t_token	*tmp;
	int		i;
	int		n;

	n = 0;
	while (l->next && !sh_sep_list(l->category))
	{
		i = 0;
		tmp = l;
		while (tmp->next && tmp->category != PIPE)
		{
			i++;
			tmp = tmp->next;
		}
		if (!(**list[n++] = sh_cmd_new(l, i)))
			return (NULL);
		l = tmp->next;
	}
	**list[n] = NULL;
	return (l);
}

static int		sh_get_list(t_cmd ****list, t_token *l, int **op)
{
	int		count_pipe;
	size_t	n;

	n = 0;
	while (l->next)
	{
		count_pipe = sh_count_pipe(l);	
		if (!(**list = (t_cmd**)ft_memalloc(sizeof(t_cmd*) * count_pipe)))
			return (-1);
		if (!(l = sh_get_cmd(*list, l, count_pipe)))
			return (-1);
		if (l->category == ANDOR)
		{
			*op[n++] = ft_strequ(l->lexeme, "&&") ? 1 : -1;
			l = l->next;
		}
		else
		{
			*op[n++] = 0;
			l = l->next;
		}
	}
	*list[n] = NULL;
	return (0);
}

int				sh_parser(t_token *lexer, t_cmd ****list, int **op)
{
	int		count;

	count = sh_count_lists(lexer);
	left = NULL;
	right = NULL;
	if (!*list && !(*list = (t_cmd***)ft_memalloc(sizeof(t_cmd**) * count)))
		return (-1);
	if (!*op && !(*op = (int*)ft_memalloc(sizeof(int) * (count - 1))))
		return (-1);
	if (ft_get_list(list, lexer, op) < 0)
		return (-1);
	return (0);
}
