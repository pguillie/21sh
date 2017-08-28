#include "shell.h"

int		sh_prompt_dollar(void)
{
	ft_putchar(ft_strequ(getenv("LOGNAME"), "root") ? '#' : '$');
	return (1);
}
