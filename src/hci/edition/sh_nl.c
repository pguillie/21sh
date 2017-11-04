#include "shell.h"

int		sh_nl(t_line *line, t_coord **coord, t_tc tc)
{
	line->cur = sh_move_cur(line->cur, line->used, *coord, tc);
	if (sh_ins(line, '\n') < 0)
		return (-1);
	return (EOL | LEXER | DISP);
}
