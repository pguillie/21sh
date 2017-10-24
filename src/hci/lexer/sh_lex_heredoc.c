#include "shell.h"

static char	*sh_lex_hd_eof(char *fifo[32])
{
	char	*eof;
	int		i;

	i = 0;
	eof = fifo[i];
	while (i < 32 && fifo[i])
	{
		fifo[i] = fifo[i + 1];
		i += 1;
	}
	return (eof);
}

static int	sh_lex_hd_rplc(t_token **list, char *hd)
{
	t_token	*l;

	l = *list;
	while (l->next && !(ft_strequ(l->lexeme, "<<")
				&& l->next->category == FILDES))
		l = l->next;
	if ((l = l->next))
	{
		//free(l->lexeme); // WTF ??????????????????????????????????????????????
		l->lexeme = hd;
		l->category = HEREDOC;
	}
	return (0);
}

int			sh_lex_eof(char *fifo[32], char *eof)
{
	int		i;

	i = 0;
	while (i < 31 && fifo[i])
		i++;
	if (i < 31)
		fifo[i] = eof;
	return (0);
}

int			sh_lex_heredoc(char *str, int *i, char *fifo[32], t_token **list)
{
	char	*heredoc;
	char	*eof;
	int		sol;
	int		len;

	sol = i[0];
	eof = sh_lex_hd_eof(fifo);
	len = ft_strlen(eof);
	while (str[sol])
	{
		i[1] = 0;
		while (str[sol + i[1]] && str[sol + i[1]] != '\n')
			i[1]++;
		if ((len == i[1] && ft_strnequ(eof, str + sol, i[1])))
			break ;
		sol += i[1] + (str[sol + i[1]] ? 1 : 0);
	}
	free(eof);
	if (!str[sol])
		return (1);
	if (!(heredoc = ft_strsub(str, i[0], sol - i[0])))
		return (-1);
	sh_lex_hd_rplc(list, heredoc);
	i[0] = sol + i[1] + 1;
	i[1] = 0;
	return (0);
}
