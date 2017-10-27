#include "shell.h"

static int	sh_display_line(t_line *line, size_t i, t_coord *coord, t_tc tc)
{
	while (line->str[i])
		ft_putchar_fd(line->str[i++], 0);
	if (line->str[i - 1] != '\n' && line->cur != i
			&& coord[i - 1].x == coord[line->used + 1].x - 1)
	{
		ft_putchar_fd(' ', 0);
		tputs(tc.le, 0, termput);
	}
	return (i);
}

static int	sh_display_color(t_line *line, t_token *lexer, size_t i, char *c)
{
	size_t	j;

	j = 0;
	ft_putstr_fd(c, 0);
	while (lexer->lexeme[j++])
		ft_putchar_fd(line->str[i++], 0);
	ft_putstr_fd(EOC, 0);
	return (i);
}

static int	sh_display_category(t_line *line, t_token *lexer, size_t i, t_tc tc)
{
	while (line->str[i])
	{
		if (lexer)
		{
			while (line->str[i] != lexer->lexeme[0] && i < line->used - 1)
				ft_putchar_fd(line->str[i++], 0);
			if (lexer->category == CMD)
				i = sh_display_color(line, lexer, i, RED);
			else if (lexer->category == ARG || lexer->category == OPT)
				i = sh_display_color(line, lexer, i, WHITE);
			else if (lexer->category <= FILDES)
				i = sh_display_color(line, lexer, i, BLUE);
			else if (lexer->category >= PIPE)
				i = sh_display_color(line, lexer, i, GREEN);
			else
				i = sh_display_color(line, lexer, i, CYAN);
		}
		else
			i = sh_display_line(line, i, tc.coord, tc);
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
		i = sh_display_category(line, lexer, i, tc);
	else
		i = sh_display_line(line, i, *coord, tc);
	lexer ? sh_token_del(&lexer) : 0;
	line->cur = sh_move_cur(i, line->pos, *coord, tc);
	return (ret == -1 ? -1 : 0);
}
