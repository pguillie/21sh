#include "shell.h"

static int	sh_last_token(t_token **list)
{
	t_token *l;

	l = *list;
	while (l->next)
		l = l->next;
	return (l->category);
}

static int	sh_lex_loop(t_token **list, char *str, int *i_stat, char *fifo[32])
{
	char	*lexeme;
	int		category;

	i_stat[1] = 0;
	if (!sh_metachar(str[i_stat[0]]))
		i_stat[1] = sh_lex_word(str + i_stat[0]);
	else if (!(i_stat[1] = sh_rdir_op(str + i_stat[0]))
			&& !(i_stat[1] = sh_ctrl_op(str + i_stat[0])))
		i_stat[0] += 1;
	if (i_stat[1])
	{
		if (!(lexeme = ft_strsub(str, i_stat[0], i_stat[1])))
			return (-1);
		if ((category = sh_category(str, i_stat, i_stat + 2)) == HEREDOC)
		{
			sh_lex_eof(fifo, lexeme);
			category = FILDES;
		}
		if (sh_token_new(list, lexeme, category))
			return (-1);
	}
	i_stat[0] += i_stat[1];
	return (0);
}

int			sh_lexer(t_token **list, char *str)
{
	char	*fifo[32];
	int		i_stat[5];
	int		ret;

	ft_memset(fifo, 0, sizeof(char*) * 32);
	ft_memset(i_stat, 0, sizeof(int) * 5);
	i_stat[2] = CMD;
	while (str[i_stat[0]])
	{
		if (i_stat[4] == 1 && fifo[0])
		{
			if ((ret = sh_lex_heredoc(str, i_stat, fifo, list)) < 0)
				return (sh_token_del(list));
			if (ret)
				return (LEX_LOOP);
		}
		if (sh_lex_loop(list, str, i_stat, fifo) < 0)
			return (sh_token_del(list));
	}
	if (sh_last_token(list) != NEWLINE || fifo[0])
		return (LEX_LOOP);
	return (LEX_OK);
}
