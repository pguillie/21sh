#include "shell.h"

static void	sh_nl_correct(t_line *line, size_t i, t_coord *coord, t_tc tc)
{
	if (line->str[i - 1] != '\n' && line->cur != i
			&& coord[i - 1].x == coord[line->used + 1].x - 1)
	{
		ft_putchar_fd(' ', 0);
		tputs(tc.le, 0, termput);
	}
}

static int	sh_display_line(t_line *line, size_t i)
{
	while (line->str[i])
		ft_putchar_fd(line->str[i++], 0);
	return (i);
}

static char	*sh_color_theme(int category)
{
	static char	*theme[10] = {
		"\e[32m",
		"\e[36m",
		"\e[33m",
		"\e[35m",
		"\e[31;1m",
		"\e[34;1m",
		"\e[30;1m",
		"",
		"\e[37;1m",
		"\e[37;1m"
	};

	return (theme[category + 5]);
}

static int	sh_display_category(t_line *line, int i)
{
	int		j;
	t_token	*lexer;
	t_token	*tmp;

	lexer = NULL;
	if (sh_lexer(&lexer, line->str) < 0)
		return (sh_token_del(&lexer));
	tmp = lexer;
	while (lexer)
	{
		j = 0;
		if (lexer->category == HEREDOC)
			lexer = lexer->next;
		ft_putstr_fd(sh_color_theme(HEREDOC), 0);
		while (!(ft_strnequ(line->str + i, lexer->lexeme,
						ft_strlen(lexer->lexeme))))
			ft_putchar_fd(line->str[i++], 0);
		ft_putstr_fd(sh_color_theme(lexer->category), 0);
		while (lexer->lexeme[j++])
			ft_putchar_fd(line->str[i++], 0);
		ft_putstr_fd(EOC, 0);
		lexer = lexer->next;
	}
	sh_token_del(&tmp);
	return (i);
}

int			sh_display(t_line *line, t_coord **coord, t_tc tc, char *save)
{
	int		i;

	line->cur = sh_move_cur(line->cur, 0, *coord, tc);
	if (sh_clear(line, coord, tc) < 0)
		return (-1);
	if (!line->used)
		return (0);
	i = 0;
	if (!save)
		i = sh_display_category(line, i);
	else
		i = sh_display_line(line, i);
	if (i < 0)
		return (-1);
	sh_nl_correct(line, i, *coord, tc);
	line->cur = sh_move_cur(i, line->pos, *coord, tc);
	return (0);
}
