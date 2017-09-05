#include "shell.h"

void	displex(t_token *lexer)
{
	ft_putendl("=== DISPLEX ===");
	while (lexer)
	{
		ft_printf("category:%2d -- lexeme:%s\n", lexer->category, lexer->lexeme);
		lexer = lexer->next;
	}
	ft_putendl(" == end lex ==");
}

void	disphist(t_line *line)
{
	ft_putendl("*** DISPHIST ***");
	while (line)
	{
		ft_printf("hist: '%s'\n", line->str);
		line = line->up;
	}
	ft_putendl(" ** end hist **");
}

void	dispcoord(t_coord *coord, t_line *line)
{
	size_t	i;

	i = 0;
	while (i <= line->used + 1)
	{
		ft_printf("%zu: (%d;%d) `%c'\n", i, coord[i].x, coord[i].y, line->str[i]);
		i++;
	}
}
