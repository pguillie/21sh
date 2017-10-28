#include "shell.h"

int		sh_i_line_modif(char *byte, t_line *line, t_line **list, int *i)
{
	if (byte[0] != '\n' && (!line->str ||
				sh_i_strstr(list[0]->str, line->str, i[2]) || byte[0] == 127))
	{
		if (byte[0] >= 32 && byte[0] <= 127)
		{
			if (byte[0] == 127)
			{
				if (line->cur)
				{
					line->cur -= 1;
					ft_memmove(line->str + line->cur, line->str + line->cur + 1,
							ft_strlen(line->str + line->cur + 1) + 1);
					line->used -= 1;
				}
			}
			else
			{
				sh_ins(line, byte[0]);
				line->cur += 1;
			}
			return (1);
		}
	}
	return (0);
}

void	sh_i_comp(t_line *line, t_line **list, t_tc *tc, int *i)
{
	if (!line->str || !line->str[0])
	{
		if (!i[2])
			while (list[1]->up)
				list[1] = list[1]->up;
		else
			while (list[1]->down)
				list[1] = list[1]->down;
	}
	if (list[0]->used && line->used > list[0]->used)
		return ;
	if (i[2])
		while ((!list[1]->str || !list[1]->str[0]) ||
		(i[2] && list[1]->up && !sh_i_strstr(list[1]->str, line->str, i[2])))
			list[1] = list[1]->up;
	else
		while (list[1]->down && !sh_i_strstr(list[1]->str, line->str, i[2]))
			list[1] = list[1]->down;
	if (list[1] && sh_i_strstr(list[1]->str, line->str, i[2]))
	{
		list[0] = list[1];
		list[0]->used = ft_strlen(list[0]->str);
		tc->coord = sh_create_coord(list[0],
				ft_strlen((list[0])->str) + 21 + ft_strlen(line->str));
	}
}

int		sh_i_line_replace(char *byte, t_line **list, t_line **line, t_tc *tc)
{
	int ret;

	ret = -1;
	if ((*line)->str[0])
	{
		free((*line)->str);
		(*line)->str = ft_strdup(list[0]->str);
		(*line)->used = ft_strlen(list[0]->str);
	}
	else
		(*line)->used = 0;
	(*line)->cur = byte[0] == 27 ? 0 : (*line)->used;
	if (byte[0] == 27)
	{
		ret = DISP;
		(*line)->pos = (*line)->cur;
	}
	else
		ret = sh_nl(*line, &tc->coord, *tc);
	return (ret);
}

void	sh_i_end(t_line *line, t_tc *tc, t_line **beg)
{
	sh_clear(line, &tc->coord, *tc);
	if (g_signal != SIGINT)
	{
		ft_putchar('\r');
		tputs(tc->ce, 0, termput);
		sh_prompt(1);
	}
	sh_hist_del(beg);
	tputs(tc->ve, 0, termput);
}

void	sh_i_begin(t_line **list, t_line *line, int *i, t_tc *tc)
{
	i[0] = 0;
	i[1] = 0;
	list[0] = sh_hist_read();
	list[2] = list[0];
	list[1] = list[0];
	while (!i[2] && list[1]->up)
		list[1] = list[1]->up;
	minedit_raz(line, tc);
	tputs(tc->vi, 0, termput);
}
