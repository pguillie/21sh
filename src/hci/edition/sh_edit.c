#include "shell.h"

int		sh_edit(t_line *line, char *last, t_token **lexer, t_tc *tc)
{
	struct termios	backup;
	char			*save;
	int				ret;

	if (term_raw(&backup, 0, 1))
		return (-1);
	ret = LEX_LOOP;
	save = NULL;
	while (ret & LEX_LOOP)
	{
		ft_bzero(line->str, line->used);
		line->used = 0;
		line->cur = 0;
		line->h_smd = 0;
		line->h_pos = 0;
		tc->esc = NULL;
		tc->prompt = sh_prompt(!save ? 1 : 2);
		if ((ret = sh_edit_line(&line, &save, lexer, tc)) < 0)
			return (sh_token_del(lexer));
		if (ret & LEX_OK)
			ret = sh_verification(*lexer);
	}
	if (tcsetattr(0, TCSANOW, &backup) < 0)
	{
		ft_error("Unable to restore termios structure", NULL, NULL);
		return (-1);
	}
	if (sh_hist_write(save, last))
		ft_error("Unable to write line in history", NULL, NULL);
	return (ret);
}
