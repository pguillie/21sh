#include "shell.h"

int		sh_prt_time(char buff[], int *b, char c)
{
	struct tm	*tm;
	time_t		t;
	int			len;

	len = 0;
	t = time(&t);
	if (t > 0 && (tm = localtime(&t)))
	{
		if (c == 't')
			len = sh_prt_strftime(buff, b, "%H:%M:%S", tm);
		else if (c == 'T')
			len = sh_prt_strftime(buff, b, "%I:%M:%S", tm);
		else if (c == '@')
			len = sh_prt_strftime(buff, b, "%I:%M %p", tm);
		else if (c == 'A')
			len = sh_prt_strftime(buff, b, "%H:%M", tm);
	}
	return (len);
}
