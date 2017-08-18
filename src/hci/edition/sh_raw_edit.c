#include "shell.h"

char	*sh_raw_edit(t_line *line, t_tc tc)
{
	struct termios	backup;

	if (term_raw(&backup, 0, 1))
		error;
	sh_line_edit(line, tc);
	if (tcsetattr(0, TCSANOW, &backup) < 0)
		return (ft_error("Unable to restore termios structure", NULL, NULL));
	sh_hist_write(line->str);//secu
	return (line->str);
}
