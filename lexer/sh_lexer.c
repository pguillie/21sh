#include "shell.h"

int		sh_lexer(t_token **list, char *str)
{
	char	*eof_fifo[32];
	char	*lexeme;
	int		category;
	int		status[2];
	int		i[2];

	i[0] = 0;
	status[0] = COMMAND;
	status[1] = 0;
	while (str[i[0]])
	{
		i[1] = 0;
		if (status[1] = 42 && eof_fifo[0])
			sh_lex_heredoc(str, i, eof_fifo, list);
		else if (!sh_metachar(str[i[0]]))
			i[1] = sh_lex_word(str + i[0]);
		else if (!(i[1] = sh_rdir_op(str + i[0]))
				&& !(i[1] = sh_ctrl_op(str + i[0])))
			i[0] += 1;
		if (i[1])
		{
			lexeme = ft_strsub(str, i[0], i[1]);//
			category = sh_category(lexeme, str + i[0] + i[1], status);
			if (category == NEWLINE)
				status[1] = 42;
			else if (category > 0)
				status[0] = COMMAND;
			else if (category == REDIR)
				status[1] = 1;
			sh_token_new(list, lexeme, category);//
		}
		i[0]++;
	}
}
