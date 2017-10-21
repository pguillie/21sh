#include "shell.h"

int		sh_prt_strftime(char buff[], int *b, char *format, struct tm *tm)
{
	char	date[128];
	int		i;
	int		len;

	len = 0;
	if (strftime(date, 128, format, tm) > 0)
	{
		i = 0;
		while (date[i])
		{
			len = (date[i] == '\n' ? 0 : len + 1);
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = date[i++];
		}
	}
	return (len);
}
