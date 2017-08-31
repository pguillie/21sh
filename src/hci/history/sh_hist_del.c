#include "shell.h"

void	sh_hist_del(t_line **hist)
{
	t_line *tmp;

	while (*hist)
	{
		tmp = *hist;
		*hist = (*hist)->up;
		ft_strdel(&tmp->str);
		ft_memdel((void**)&tmp);
	}
}
