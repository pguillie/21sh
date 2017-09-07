#include "shell.h"

static int	sh_convert_del(char *esc)
{
	if (esc[1] == '[' && esc[2] == '3' && esc[3] == '~')
		return (DEL_R);
	return (0);
}

int			sh_del_able(char *esc, t_line *line)
{
	int	id;

	id = sh_convert_del(esc);
	if (id & DEL_R && line->cur != line->used)
		return (1);
	return (0);
}
