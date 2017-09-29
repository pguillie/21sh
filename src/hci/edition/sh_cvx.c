#include "shell.h"

int		sh_cvx(t_line *line, t_coord **coord, t_tc *tc, char byte)
{
	int	ret;

	ret = 0;
	if (byte == 11)
	{
		if (tc->cut == 0 && tc->clipboard)
			ft_strclr(tc->clipboard);
		ret = sh_cut_k(line, coord, tc);
	}
	else if (byte == 21)
	{
		if (tc->cut == 0 && tc->clipboard)
			ft_strclr(tc->clipboard);
		ret = sh_cut_u(line, coord, tc);
	}
	else if (byte == 23)
	{
		if (tc->cut == 0 && tc->clipboard)
			ft_strclr(tc->clipboard);
		ret = sh_cut_w(line, coord, tc);
	}
	if (byte == 25)
	{
		ret = sh_paste(line, coord, tc);
		tc->cut = 0;
	}
	else
		tc->cut = 1;
	return (ret);
}
