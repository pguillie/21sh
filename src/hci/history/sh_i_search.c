#include "shell.h"

void	minedit_raz(t_line *line, t_tc *tc)
{
	ft_bzero(line->str, line->used);
	line->used = 0;
	line->cur = 0;
	line->h_smd = 0;
	line->h_pos = 0;
	tc->esc = NULL;
}

int		sh_i_strstr(char *file, char *line, int r)
{
	if (r && ft_strrstr(file, line))
		return (1);
	else if (ft_strstr(file, line))
		return (1);
	return (0);
}

int		sh_i_high(t_line **list, t_line *line)
{
	t_coord *test;

	test = sh_create_coord(line, (list ?
		ft_strlen(list[0]->str) : 0) + 21 + ft_strlen(line->str));
	return (test->y);
}

int		sh_i_search(t_line *line, t_tc *tc, int mode)
{
	t_line	*list[3];
	int		i[3];
	char	byte[8];

	i[2] = mode;
	sh_i_begin(list, line, i, tc);
	ft_bzero(byte, 8);
	while (byte[0] != '\n' && byte[0] != 27 && g_signal != SIGINT
			&& !(i[0] & EOT) && !(i[0] & EOL) && !(i[0] < 0))
	{
		sh_print_file(list, line, tc, i);
		ft_bzero(byte, 8);
		if (read(0, &byte, 8) < 0 && g_signal != SIGWINCH)
			i[0] = -1;
		if (sh_i_line_modif(byte, line, list, i))
			sh_i_comp(line, list, tc, i);
	}
	if (byte[0] == 27 || (sh_i_strstr(list[0]->str, line->str, i[2])
		&& byte[0] == '\n'))
		i[0] = sh_i_line_replace(byte, list, &line, tc);
	else
		minedit_raz(line, tc);
	sh_i_end(line, tc, &list[2]);
	return (i[0]);
}
