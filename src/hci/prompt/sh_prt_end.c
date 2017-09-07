#include "shell.h"

int		sh_prt_end(void)
{
	ft_putchar(ft_strequ(getenv("LOGNAME"), "root") ? '#' : '$');
	return (1);
}
