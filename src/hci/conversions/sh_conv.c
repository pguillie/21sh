#include "shell.h"

/*
**	add to line:37
**	if (str[0] == 'u')
**		return (sh_conv_hex(str, 4));
**	if (str[0] == 'U')
**		return (sh_conv_hex(str, 8));
*/

static char	sh_conv_char(char *str)
{
	if (str[0] == 'a')
		return ('\a');
	if (str[0] == 'b')
		return ('\b');
	if (str[0] == 'e' || str[0] == 'E')
		return (27);
	if (str[0] == 'f')
		return ('\f');
	if (str[0] == 'n')
		return ('\n');
	if (str[0] == 't')
		return ('\t');
	if (str[0] == 'v')
		return ('\v');
	return (0);
}

char		sh_conv(char *str)
{
	if (str[0] == '0')
		return (sh_conv_oct(str + 1));
	if (str[0] == 'x')
		return (sh_conv_hex(str + 1));
	return (sh_conv_char(str));
}
