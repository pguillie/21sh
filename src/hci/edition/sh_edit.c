#include "shell.h"

static int	edit_end(struct termios backup, int ret, char *save, char *last)
{
	if (tcsetattr(0, TCSANOW, &backup) < 0)
	{
		save ? ft_strdel(&save) : 0;
		ft_error("Unable to restore termios structure", NULL, NULL);
		return (-1);
	}
	if (!(ret & EOT) && g_signal != SIGINT)
	{
		if (sh_hist_write(save, last))
			ft_error("Unable to write line in history", NULL, NULL);
	}
	save ? ft_strdel(&save) : 0;
	return (ret);
}

int			sh_edit(t_line *line, char *last, t_token **lexer, t_tc *tc)
{
	struct termios	backup;
	char			*save;
	int				ret;

	if (term_raw(&backup, 0, 1))
		return (-1);
	ret = LEX_LOOP;
	save = NULL;
	while (g_signal != SIGINT && !(ret & EOT) && ret & LEX_LOOP)
	{
		ft_bzero(line->str, line->used);
		line->used = 0;
		line->cur = 0;
		tc->esc = NULL;
		tc->prompt = sh_prompt(!save ? 1 : 2);
		if ((ret = sh_edit_line(&line, &save, lexer, tc)) < 0)
			return (sh_token_del(lexer));
		if (ret & LEX_OK)
			ret = sh_verification(*lexer);
	}
	return (edit_end(backup, ret, save, last));
}
