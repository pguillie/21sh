#include "shell.h"

int		sh_prt_date(void)
{
	char	*date;
	time_t	t;

	if (time(&t) < 0 || !(date = ctime(&t)))
		return (0);
	date[10] = '\0';
	ft_putstr(date);
	return (10);
}
