#include "shell.h"

/*
**	RETURN STATUS:
**
**	-1	crash
**	 0	valid
**	 1	pas fini
**	 2	syntax error (lexer ou parser?)
*/

static t_token	*sh_lex_token(char *lexeme, int *status, t_token **begin, t_token *cur)
{
	t_token		*new;

	if (!(new = sh_token_new(lexeme, status)))
	{
		sh_token_del(begin);
		return (NULL);
	}
	if (!*begin)
	{
		*begin = new;
		cur = new;
	}
	else
	{
		cur->next = new;
		cur = cur->next;
	}
	return (cur);
}

int				sh_lexer(char *str, t_token **begin)
{
	t_token		*cur;
	size_t		i[2];
	int			status;

	if (!str)
		return (-1);
	if (!str[0])
		return (0);
	i[0] = 0;
	sh_token_del(begin);
	cur = NULL;
	status = CMD;
	while (str[i[0]])
	{
		i[1] = 0;
		if (!sh_metachar(str[i[0]]))
			i[1] = sh_lex_word(str + i[0]);
		else if (!(i[1] = sh_ctrl_op(str + i[0]) + sh_rdir_op(str + i[0])))
			i[0] += 1;
		if (i[1])
		{
			if (!(cur = sh_lex_token(ft_strsub(str, i[0], i[1]),
						&status, begin, cur)))
				return (-1);
			i[0] += i[1];
		}
	}
	if (cur->category == NEWLINE)
		return (0);
	return (1);
}
