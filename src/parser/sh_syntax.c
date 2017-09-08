#include "shell.h"

int		sh_syntax(t_token *lexer)
{
	if (lexer->category != CMD && !ft_strequ(lexer->lexeme, ";")
			&& lexer->category != FILDES && lexer->category != REDIRECTION)
		return (ft_error("sla_sh", "syntax error near unexpected token"
					, lexer->lexeme));
	while (lexer->next)
	{
		if (lexer->category >= 0 && lexer->category != ESPERCOLON
				&& lexer->next->category >= 0 
				&& !ft_strequ(lexer->lexeme, ";"))
			return (ft_error("sla_sh", "syntax error near unexpected token"
					, ft_strequ(lexer->next->lexeme, "\n") ? "newline" :
					lexer->next->lexeme));
		lexer = lexer->next;
	}
	return (0);
}
