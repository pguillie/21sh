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
