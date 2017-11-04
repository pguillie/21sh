#include "shell.h"

static void	sh_i_print(t_line *line, char *str, t_tc *tc, int mode)
{
	int			y;

	tputs(tc->cd, 0, termput);
	sh_i_prompt(str, tc, mode);
	ft_putstr(line->str);
	free(tc->coord);
	tc->coord = sh_create_coord(line, 21 + ft_strlen(str));
	y = tc->coord[line->used].y;
	while (y--)
		tputs(tc->up, 0, termput);
	ft_putstr("\r");
}

static int	sh_i_strstr(char *line, char *str, int mode)
{
	if (mode == 0)
	{
		if (ft_strrstr(line, str) != NULL)
			return (1);
	}
	else if (line)
	{
		if (ft_strstr(line, str) != NULL)
			return (1);
	}
	return (0);
}

static void	sh_i_find(t_line **glob, t_tc *tc, char *tmp, int mode)
{
	int		ret;

	while (glob[0])
	{
		ret = 0;
		if ((ret = sh_i_strstr(glob[0]->str, tmp, mode)))
		{
			sh_i_print(glob[0], tmp, tc, mode);
			break ;
		}
		glob[0] = (mode == 0 ? glob[0]->up : glob[0]->down);
	}
	if (ret == 1)
		glob[1] = glob[0];
	else if (sh_i_strstr(glob[1]->str, tmp, mode))
		sh_i_print(glob[1], tmp, tc, mode);
}

static int	sh_i_read(t_line **glob, t_tc *tc, int mode)
{
	char	*tmp;
	char	byte[8];

	tmp = NULL;
	ft_bzero(byte, 8);
	if (!glob[0]->str[0])
		glob[0] = glob[0]->up;
	while (read(0, &byte, 8) >= 0 && byte[0] != '\n' && g_signal != SIGINT)
	{
		if (byte[0] == 27 || g_signal == SIGWINCH)
		{
			free(tmp);
			return (1);
		}
		else if (byte[0] == 127)
		{
			tmp = sh_del_char(tmp);
			glob[0] = glob[1];
		}
		else
			tmp = sh_ins_char(tmp, byte[0]);
		sh_i_find(glob, tc, tmp, mode);
	}
	free(tmp);
	return (glob[1] ? 0 : 1);
}

int			sh_i_search(t_line **line, t_tc *tc, int mode)
{
	t_line	*glob[2];
	int		ret;

	(*line)->pos = sh_move_cur((*line)->pos, 0, tc->coord, *tc);
	(*line)->cur = 0;
	glob[0] = *line;
	glob[1] = *line;
	sh_i_print(glob[0], NULL, tc, mode);
	if (mode == 1)
		while (glob[0]->up)
			glob[0] = glob[0]->up;
	ret = sh_i_read(glob, tc, mode);
	*line = glob[1];
	tputs(tc->cd, 0, termput);
	free(tc->coord);
	tc->coord = sh_create_coord(*line, sh_prompt(1));
	g_signal = 0;
	*line ? tc->coord[(*line)->used].y = 0 : 1;
	if (ret == 0)
	{
		*line ? ft_putstr((*line)->str) : 1;
		(*line)->cur = (*line)->used;
		return (sh_nl(*line, &tc->coord, *tc));
	}
	return (DISP);
}
