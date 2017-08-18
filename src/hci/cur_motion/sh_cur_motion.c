#include "shell.h"

size_t	sh_cur_motion(size_t origin, size_t dest, t_tc tc)
{
	int		move;

	move = dest - origin;
	while (move)
	{
		tputs(move > 0 ? tc.nd : tc.le, 0, termput);
		move += move > 0 ? -1 : 1;
	}
	return (dest);
}
