#include "shell.h"

static void	sh_print_i_prompt(int mode, t_tc *tc, char *line)
{
	if (!mode)
		ft_putstr("\r(forward-i-search)`");
	else
		ft_putstr("\r(reverse-i-search)`");
	tputs(tc->ce, 0, termput);
	ft_putstr(line);
	ft_putstr("\': ");
}

static int	sh_print_i_suite(t_line **list, t_line *line, t_tc *tc, int *j)
{
	int pos;
	int i;

	if (line->used > list[0]->used)
		return (-1);
	pos = -1;
	i = j[2] ? 0 : (list[0]->used - 1);
	while ((--j[1] + 1) > 0)
		tputs(tc->up, 0, termput);
	ft_putchar('\r');
	tputs(tc->cd, 0, termput);
	sh_print_i_prompt(j[2], tc, line->str);
	if (!line->str[0])
	{
		j[1] = 0;
		return (-1);
	}
	while (list[0]->used >= line->used && list[0]->str[i])
	{
		if (ft_strnequ(list[0]->str + i, line->str, line->used))
			pos = i;
		i += j[2] ? 1 : -1;
	}
	return (pos);
}

void		sh_print_file(t_line **list, t_line *line, t_tc *tc, int *j)
{
	int i[4];

	if ((i[3] = sh_print_i_suite(list, line, tc, j)) < 0)
		return ;
	i[2] = 0;
	i[0] = 0;
	i[1] = line->used;
	while (list[0]->str[i[0]])
	{
		if (i[0] == i[3])
		{
			tputs(tgetstr("mr", 0), 0, termput);
			i[2] = 1;
		}
		ft_putchar(list[0]->str[i[0]]);
		if (i[2])
			i[1]--;
		if (i[1] == 0)
			tputs(tgetstr("me", 0), 0, termput);
		i[0]++;
	}
	tputs(tgetstr("me", 0), 0, termput);
	j[1] = tc->coord->y;
}
