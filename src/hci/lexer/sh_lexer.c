#include "shell.h"

/*
**	RETURN STATUS:
**
**	-1	crash
**	 0	valid
**	 1	pas fini
**	 2	syntax error (lexer ou parser?)
*/

static int	sh_lex_token(char *lexeme, int *status, t_token **begin)
{
	t_token		*new;
	t_token		*browse;

	browse = *begin;
	if (!(new = sh_token_new(lexeme, status)))
	{
		sh_token_del(begin);
		return (-1);
	}
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

static int	sh_lex_loop(char *str, size_t *i, int *status, t_token **begin)
{
	int		l;

	l = 0;
	if (!sh_metachar(str[*i]))
		l = sh_lex_word(str + *i);
	else if (!(l = sh_ctrl_op(str + *i) + sh_rdir_op(str + *i)))
		*i += 1;
	if (l)
	{
		if (sh_lex_token(ft_strsub(str, *i, l), status, begin) == -1)
			return (-1);
		*i += l;
	}
	return (0);
}

int			sh_lexer(char *str, t_token **begin)
{
	t_token		*last;
	size_t		i;
	int			status;

	if (!str)
		return (-1);
	sh_token_del(begin);
	status = CMD;
	i = 0;
	if (str)
		while (str[i])
			if (sh_lex_loop(str, &i, &status, begin) < 0)
				return (-1);
	last = *begin;
	if (last)
		while (last->next)
			last = last->next;
	if (last && last->category == NEWLINE)
		return (0);
	if ((i == 0 || sh_metachar(str[i - 1]))
				&& (sh_lex_token(ft_strdup(""), &status, begin) != -1))
		return (-1);
	return (1);
}
