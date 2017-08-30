#include "shell.h"

/*
**	RETURN STATUS:
**
**	-1	crash
**	 0	valid
**	 1	pas fini
**	 2	syntax error (lexer ou parser?)
*/

static int	sh_lex_token(char *str, size_t *i, int *status, t_token **begin)
{
	t_token		*new;
	t_token		*browse;

	if (!(new = sh_token_new(str, i, status)))
	{
		sh_token_del(begin);
		return (-1);
	}
	status[1] = new->category == REDIRECTION ? 1 : 0;
	browse = *begin;
	if (!browse)
	{
		*begin = new;
		return (0);
	}
	while (browse->next)
		browse = browse->next;
	browse->next = new;
	return (0);
}

static int	sh_lex_loop(char *str, int *status, t_token **begin)
{
	size_t	i[2];

	i[0] = 0;
	while (str[i[0]])
	{
		i[1] = 0;
		if (!sh_metachar(str[i[0]]))
			i[1] = sh_lex_word(str + i[0]);
		else if (!(i[1] = sh_ctrl_op(str + i[0]) + sh_rdir_op(str + i[0])))
			i[0] += 1;
		if (i[1])
		{
			if (sh_lex_token(str, i, status, begin) == -1)
				return (-1);
			i[0] += i[1];
		}
	}
	return (0);
}

int			sh_lexer(char *str, t_token **begin)
{
	t_token		*last;
	int			status[2];

	if (!str)
		return (-1);
	sh_token_del(begin);
	status[0] = CMD;
	status[1] = 0;
	if (str && sh_lex_loop(str, status, begin) < 0)
		return (-1);
	last = *begin;
	if (last)
		while (last->next)
			last = last->next;
	if (last && last->category == NEWLINE)
		return (0);
	if ((!str[0] || sh_metachar(str[ft_strlen(str) - 1]))
			&& (sh_lex_token(NULL, NULL, status, begin) != -1))
		return (-1);
	return (1);
}
