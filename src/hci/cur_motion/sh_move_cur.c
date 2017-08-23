#include "shell.h"

size_t	sh_move_cur(size_t pos, size_t dest, t_coord *coord, t_tc tc)
{
	struct termios	term;
	int				move;

	if (tcgetattr(0, &term) < 0)
		return (ft_error("Unable to get the termios structure", NULL, NULL));
	term.c_oflag &= ~OPOST;
	if (tcsetattr(0, TCSANOW, &term) < 0)
		return (ft_error("Unable to set raw termios structure", NULL, NULL));
	move = coord[dest].y - coord[pos].y;
	while (move)
	{
		tputs(move > 0 ? tc.dn : tc.up, 0, termput);
		move += move < 0 ? 1 : -1;
//		usleep(100000);
	}
	move = coord[dest].x - coord[pos].x;
	while (move)
	{
		tputs(move > 0 ? tc.nd : tc.le, 0, termput);
		move += move < 0 ? 1 : -1;
//		usleep(100000);
	}
	term.c_oflag |= OPOST;
	if (tcsetattr(0, TCSANOW, &term) < 0)
		return (ft_error("Unable to set raw termios structure", NULL, NULL));
	return (dest);
}
