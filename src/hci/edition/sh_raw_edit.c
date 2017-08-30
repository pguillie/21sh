#include "shell.h"

int		sh_raw_edit(t_line *line, char *last, t_token **lexer, t_tc tc)
{
	struct termios	backup;
	char			*save;
	int				failure;

	if (term_raw(&backup, 0, 1))
		return (-1);
	failure = 1;
	save = NULL;
	while (failure)
	{
		ft_bzero(line->str, line->used);
		line->used = 0;
		line->cur = 0;
		tc.prompt = sh_prompt(!save ? 1 : 2);
		failure = sh_line_edit(&line, &save, lexer, tc);
	}
	if (tcsetattr(0, TCSANOW, &backup) < 0)
	{
		ft_error("Unable to restore termios structure", NULL, NULL);
		return (-1);
	}
	if (sh_hist_write(save, last))
		ft_error("Unable to write line in history", NULL, NULL);
	return (0);
}
