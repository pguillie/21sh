#include "shell.h"

static int		sh_count_pipeline(t_token *l, int **op)
{
	t_token	*a;
	int		i;
	int		j;

	i = 0;
	a = l;
	while (l->next)
	{
		if (l->category > PIPE && l->next->category != NEWLINE
				&& l->next->next)
			i++;
		l = l->next;
	}
	if (!(*op = (int*)ft_memalloc(sizeof(int) * (i + 1))))
		return (-1);
	j = 0;
	while (a->next)
	{
		if (a->category == ANDOR)
			(*op)[j++] = ft_strequ(a->lexeme, "&&") ? 1 : -1;
		else if (a->category > 1)
			(*op)[j++] = 0;
		a = a->next;
	}
	return (i + 1);
}

static int		sh_count_cmd(t_token *l)
{
	int		i;

	i = 0;
	while (l->next && l->category <= PIPE)
	{
		if (l->category == PIPE)
			i++;
		l = l->next;
	}
	return (i + 1);
}

static t_cmd	**sh_get_pipeline(t_token *lexer)
{
	t_cmd	**pipeline;
	int		count;
	int		i;

	count = sh_count_cmd(lexer);
	if (!(pipeline = (t_cmd**)ft_memalloc(sizeof(t_cmd*) * (count + 1))))
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (i && lexer->category < PIPE)
			lexer = lexer->next;
		lexer = i ? lexer->next : lexer;
		if (!(pipeline[i++] = sh_cmd_new(lexer)))
			return (NULL);
	}
	return (pipeline);
}

int				sh_parser(t_token *lexer, t_cmd ****list, int **op)
{
	int		count;
	int		i;

	if (!lexer)
		return (0);
	count = sh_count_pipeline(lexer, op);
	if (!(*list = (t_cmd***)ft_memalloc(sizeof(t_cmd**) * (count + 1))))
		return (-1);
	i = 0;
	while (i < count)
	{
		while (lexer->next && lexer->category > 1)
			lexer = lexer->next;
		if (!((*list)[i++] = sh_get_pipeline(lexer)))
			return (sh_list_del(list, op));
		while (lexer->next && lexer->category < 2)
			lexer = lexer->next;
	}
	return (0);
}
