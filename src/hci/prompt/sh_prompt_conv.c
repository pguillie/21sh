#include "shell.h"

int		sh_prompt_conv(char *str)
{
	char	c;

	if (str[0] == 'u')
		return (sh_prompt_user());
	if (str[0] == 'h')
		return (sh_prompt_host());
	if (str[0] == 'w')
		return (sh_prompt_workdir());
	if (str[0] == '$')
		return (sh_prompt_dollar());
	c = sh_conv(str);
	ft_putchar(c);
	return (0);
}
