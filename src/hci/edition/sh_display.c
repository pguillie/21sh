#include "shell.h"

static void	sh_disp_nl(t_line *line, t_coord *coord, t_tc tc)
{
	if (line->used && line->str[line->used - 1] != '\n'
			&& line->cur != line->used
			&& coord[line->used - 1].x == coord[line->used + 1].x - 1)
	{
		ft_putchar_fd(' ', 0);
		tputs(tc.le, 0, termput);
	}
}

int			sh_display(t_line *line, t_coord **coord, t_tc tc, char *save)
{
	t_token	*lexer;
	char	*syntax;

	syntax = getenv("SYNTAX");
	lexer = NULL;
	if (!syntax || !ft_strequ(syntax, "ON") || save)
	{
		if (sh_clear(line, coord, tc) < 0)
			return (-1);
		ft_putstr_fd(line->str + line->cur, 0);
	}
	else
	{
		line->cur = sh_move_cur(line->cur, 0, *coord, tc);
		if (sh_clear(line, coord, tc) < 0)
			return (-1);
		sh_display_syntax(line->str);
	}
	sh_disp_nl(line, *coord, tc);
	line->cur = sh_move_cur(line->used, line->pos, *coord, tc);
	return (0);
}
