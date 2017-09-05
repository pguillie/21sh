#include "shell.h"

/*
**	RETURN STATUS:
**
**	-1	malloc error
**	 0	ok
**	 1	ko
*/

int		sh_edit(t_line *line, char *last, t_token **lexer, t_tc *tc)
{
	struct termios	backup;
	char			*save;
	int				loop;

	if (term_raw(&backup, 0, 1))
		return (1);
	loop = 1;
	save = NULL;
	while (loop)
	{
		ft_bzero(line->str, line->used);
		line->used = 0;
		line->cur = 0;
		tc->esc = NULL;
		tc->prompt = sh_prompt(!save ? 1 : 2);
		if ((loop = sh_edit_line(&line, &save, lexer, tc)) < 0)
			return (sh_token_del(lexer));
	}
	if (tcsetattr(0, TCSANOW, &backup) < 0)
		return (ft_error("Unable to restore termios structure", NULL, NULL));
	if (sh_hist_write(save, last))
		ft_error("Unable to write line in history", NULL, NULL);
	return (0);
}
