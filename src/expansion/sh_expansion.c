#include "shell.h"

/*
**		in that order:
**	brace expansion
**	tilde expansion
**	parameter and variable expansion
**	command substitution
**	arithmetic expansion
**	word splitting
**	filename expansion
*/

static size_t	sh_norminette(char **lex, size_t i, size_t j, char *quote)
{
	if ((*lex)[i] == *quote)
		*quote = 0;
	else if (((*lex)[i] == '\'' || (*lex)[i] == '\"' || (*lex)[i] == '`')
			&& !*quote)
		*quote = (*lex)[i];
	else
		(*lex)[j++] = (*lex)[i];
	return (j);
}

static char		*sh_rm_quote(char *lex)
{
	size_t	i;
	size_t	j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (lex[i])
	{
		if (lex[i] == '\\' && quote != '\'')
		{
			if (lex[++i] != '\n')
				lex[j++] = lex[i];
		}
		else
			j = sh_norminette(&lex, i, j, &quote);
		i++;
	}
	ft_strclr(lex + j);
	return (lex);
}

t_token			*sh_expansion(t_token *lexer)
{
	t_token	*expa;

	if (lexer)
	{
		expa = lexer;
		while (expa)
		{
			expa->lexeme = sh_exp_tilde(expa->lexeme);
			sh_rm_quote(expa->lexeme);
			expa = expa->next;
		}
	}
	return (lexer);
}
