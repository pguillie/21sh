#include "shell.h"

static int	sh_last_token(t_token **list)
{
	t_token *l;

	l = *list;
	while (l->next)
		l = l->next;
	return (l->category);
}

int		sh_lexer(t_token **list, char *str)
{
	char	*eof_fifo[32];
	char	*lexeme;
	int		category;
	int		status[3];
	int		i[2];

	i[0] = 0;
	ft_memset(eof_fifo, 0, sizeof(char*) * 32);
	status[0] = CMD;
	status[1] = 0;
	status[2] = 0;
	while (str[i[0]])
	{
		printf("STATUS: %d\n", status[1]);
		dispeof(eof_fifo);
		i[1] = 0;
		printf("NEWLINE? %d\n", status[2]);
		if (status[2] == 1 && eof_fifo[0])
		{
			printf("-- ENTER HEREDOC --\n");
			if (sh_lex_heredoc(str, i, eof_fifo, list))
				return (LEX_LOOP);//a voir
		}
		if (!sh_metachar(str[i[0]]))
			i[1] = sh_lex_word(str + i[0]);
		else if (!(i[1] = sh_rdir_op(str + i[0]))
				&& !(i[1] = sh_ctrl_op(str + i[0])))
			i[0] += 1;
		if (i[1])
		{
			lexeme = ft_strsub(str, i[0], i[1]);//
			if ((category = sh_category(str, i, status)) == HEREDOC)
			{
				sh_lex_eof(eof_fifo, lexeme);
				category = FILDES;
			}
			sh_token_new(list, lexeme, category);//
		}
		i[0] += i[1];
	}
	if (sh_last_token(list) != NEWLINE || /*status[2]*/ eof_fifo[0])
		return (LEX_LOOP);
	return (LEX_OK);
}
