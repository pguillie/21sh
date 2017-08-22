#include "shell.h"
/*
int		sh_ckd_edit(void)
{
	char	*line[3];
	int		success[2];

	line[0] = NULL;
	success[0] = 0;
	while (success[0] != 1)
	{
		sh_prompt(line[0] == NULL ? 1 : 2);
		line[2] = line[0];
		success[1] = get_next_line(0, &line[1]) != -1
			&& (line[0] = ft_strcjoin(line[2], line[1], '\n'));
		line[1] ? ft_strdel(&line[1]) : 0;
		line[2] ? ft_strdel(&line[2]) : 0;
		if (!success[1])
		{
			line[0] ? ft_strdel(&line[0]) : 0;
			return (ft_error(term->prg, "Unable to append new line", NULL));
		}
		if ((success[0] = sh_lexer(term->prg, line[0], &lexer)) < 0)
			return (sh_token_del(&lexer) - 1);
	}
	if (sh_hist_nl(line[0], term))
		ft_printf("%s: Unable to append new line to history file\n", term->prg);
	ft_strdel(&line[0]);
	return (0);
}
*/
