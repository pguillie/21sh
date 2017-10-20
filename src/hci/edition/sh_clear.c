#include "shell.h"

void	sh_clear(t_line *line, t_coord *coord, t_tc tc)
{
	int		i;

	tputs(tc.ce, 0, termput);
	ft_putstr("\n\r");
	tputs(tc.cd, 0, termput);
	tputs(tc.up, 0, termput);
	i = 0;
	while (i++ < coord[line->cur].x)
		tputs(tc.nd, 0, termput);
}
