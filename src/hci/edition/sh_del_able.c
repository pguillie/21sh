#include "shell.h"

int			sh_del_able(char *esc, t_line *line)
{
	return (esc[1] == '[' && esc[2] == '3' && esc[3] == '~'
		&& line->cur != line->used);
}
