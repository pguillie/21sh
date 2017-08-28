#include "shell.h"

int		sh_metachar(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '|' || c == '&'
			|| c == ';' || c == '(' || c == ')' || c == '<' || c == '>');
}
