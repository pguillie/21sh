#include "shell.h"

int		sh_prt_date(char buff[], int *b, char *ps, int *len)
{
	struct tm	*tm;
	time_t		t;
	int			i;
	char		tmp;

	i = 1;
	t = time(&t);
	if (t > 0 && (tm = localtime(&t)))
	{
		if (ps[0] == 'd')
			*len = sh_prt_strftime(buff, b, "%a %b %d", tm);
		else if (ps[i] == '{')
		{
			while (ps[i] && ps[i] != '}')
				i++;
			tmp = ps[i];
			ps[i] = '\0';
			*len = sh_prt_strftime(buff, b, i > 2 ? ps + 2 : "%X", tm);
			ps[i++] = tmp;
		}
		else
			return (0);
		return (i);
	}
	return (0);
}
