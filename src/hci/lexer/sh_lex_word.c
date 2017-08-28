#include "shell.h"

int		sh_lex_word(char *str)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (str[i] && (quote || !sh_metachar(str[i])))
	{
		if (str[i] == '\\' && str[i + 1])
			i++;
		else
		{
			if (str[i] == quote)
				quote = 0;
			else if ((str[i] == '\"' || str[i] == '\'' || str[i] == '`') && !quote)
				quote = str[i];
		}
		i++;
	}
	return (i);
}
