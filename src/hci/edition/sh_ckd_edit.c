#include "shell.h"

int		sh_ckd_edit(t_token **begin)
{
	char	*line[3];
	int		success[2];

	line[0] = NULL;
	success[0] = 1;
	while (success[0] == 1)
	{
		sh_prompt(line[0] == NULL ? 1 : 2);
		line[2] = line[0];
		success[1] = get_next_line(0, &line[1]) != -1
			&& (line[0] = ft_strjoin(line[2], line[1]));
		line[1] ? ft_strdel(&line[1]) : 0;
		line[2] ? ft_strdel(&line[2]) : 0;
		if (!success[1])
		{
			line[0] ? ft_strdel(&line[0]) : 0;
			return (ft_error("Unable to append new line", NULL, NULL));
		}
		if ((success[0] = sh_lexer(line[0], begin)) < 0)
			return (-1);//sh_token_del(&lexer) - 1);
	}
	if (sh_hist_write(line[0], NULL))
		ft_error("Unable to append new line to history file", NULL, NULL);
	ft_strdel(&line[0]);
	return (0);
}
