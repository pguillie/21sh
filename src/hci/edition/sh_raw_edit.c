#include "shell.h"

char	*sh_raw_edit(t_line *line, char *last, t_tc tc)
{
	struct termios	backup;
	int				prompt;

	if (term_raw(&backup, 0, 1))
		return (NULL);
	prompt = sh_prompt(1);
	sh_line_edit(line, prompt, tc);
	if (tcsetattr(0, TCSANOW, &backup) < 0)
	{
		ft_error("Unable to restore termios structure", NULL, NULL);
		return (NULL);
	}
	if (sh_hist_write(line->str, last))
		ft_error("Unable to write line in history", NULL, NULL);
	return (line->str);
}
