#include "shell.h"

static int	edit_end(t_token **lexer, int ret, char *save, char *last)
{
	if (ret < 0 || ret & EOT || ret & SYN_ERR)
		sh_token_del(lexer);
	else if (sh_hist_write(save, last))
		ft_error("Unable to write line in history", NULL, NULL);
	save ? ft_strdel(&save) : 0;
	return (g_signal == SIGINT ? 1 : ret);
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
	while (ret & LEX_LOOP)
	{
		g_signal = 0;
		ft_bzero(line->str, line->used);
		line->used = 0;
		line->cur = 0;
		line->h_smd = 0;
		line->h_pos = 0;
		tc->esc = NULL;
		tc->prompt = sh_prompt(!save ? 1 : 2);
		ret = sh_edit_line(&line, &save, lexer, tc);
		if (ret < 0 || ret == EOT)
			break ;
		if (ret & LEX_OK)
			ret = sh_verification(*lexer);
	}
	if (tcsetattr(0, TCSANOW, &backup) < 0 && (ret = -1))
		ft_error("Unable to restore termios structure", NULL, NULL);
	return (edit_end(lexer, ret, save, last));
}
