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

static int	sh_display_line(t_line *line, size_t i)//, t_coord *coord, t_tc tc)
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

static int	sh_display_category(t_line *line, t_token *lexer, size_t i)//, t_tc tc)
{
	size_t	j;

	while (line->str[i])
	{
		if (lexer)
		{
			while (line->str[i] != lexer->lexeme[0] && i < line->used - 1)
				ft_putchar_fd(line->str[i++], 0);
			ft_putstr_fd(sh_color_theme(lexer->category), 0);
			j = 0;
			while (lexer->lexeme[j++])
				ft_putchar_fd(line->str[i++], 0);
			ft_putstr_fd(EOC, 0);
		}
		else
			i = sh_display_line(line, i);//, tc.coord, tc);
		lexer = (lexer ? lexer->next : NULL);
	}
	return (i);
}

int			sh_display(t_line *line, t_coord **coord, t_tc tc, char *save)
{
	size_t	i;
	t_token	*lexer;
	int		ret;

	line->cur = sh_move_cur(line->cur, 0, *coord, tc);
	if (sh_clear(line, coord, tc) < 0)
		return (-1);
	if (!line->used)
		return (0);
	lexer = NULL;
	i = 0;
	ret = sh_lexer(&lexer, line->str);
	if (!save)
		i = sh_display_category(line, lexer, i);//, tc);
	else
		i = sh_display_line(line, i);//, *coord, tc);
	sh_nl_correct(line, i, *coord, tc);
	lexer ? sh_token_del(&lexer) : 0;
	line->cur = sh_move_cur(i, line->pos, *coord, tc);
	return (ret == -1 ? -1 : 0);
}
