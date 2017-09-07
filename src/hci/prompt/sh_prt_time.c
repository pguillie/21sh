#include "shell.h"

int		sh_prt_time(char c)
{
	struct tm	*tm;
	time_t		t;
	int			hour;

	if (time(&t) < 0 || !(tm = localtime(&t)))
		return (0);
	hour = tm->tm_hour % 12;
	hour = hour ? hour : 12;
	if (c == 't')
		ft_printf("%.2d:%.2d:%.2d", tm->tm_hour, tm->tm_min, tm->tm_sec);
	if (c == 'T')
		ft_printf("%.2d:%.2d:%.2d", hour, tm->tm_min, tm->tm_sec);
	if (c == '@')
		ft_printf("%.2d:%.2d %s", hour, tm->tm_min,
				tm->tm_hour < 12 ? "AM" : "PM");
	if (c == 'A')
		ft_printf("%.2d:%.2d", tm->tm_hour, tm->tm_min);
	return (c == 'A' ? 5 : 8);
}
