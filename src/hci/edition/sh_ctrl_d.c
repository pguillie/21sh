#include "shell.h"

int		sh_ctrl_d(t_line *line, t_coord **coord, t_tc tc, char *save)
{
	if (line->str[line->cur])
		return (sh_del_r(line, coord, tc));
	else if (line->cur == 0 && !save)
		return (EOT);
	return (0);
}
