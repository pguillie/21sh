#include "shell.h"

int		sh_esc(t_line **line, t_coord **coord, t_tc *tc, int *hist_search_mode)
{
	char	byte;
	size_t	size;

	if (!(tc->esc = ft_strnew(2)))
		return (-1);
	tc->esc[0] = 27;
	if (read(0, &tc->esc[1], 1) < 0)
	{
		ft_strdel(&tc->esc);
		return (-1);
	}
	if (tc->esc[1] == '[' && (size = 2))
	{
		byte = 0;
		while (byte < '@' || byte > '~')
		{
			if (!(tc->esc = ft_realloc(tc->esc, size, size + 1, sizeof(char))))
				return (-1);
			if (tc->esc && read(0, &byte, 1) < 0)
				free(tc->esc);
			if (!tc->esc)
				return (-1);
			tc->esc[size++] = byte;
		}
	}
	return (sh_putesc(line, coord, tc, hist_search_mode));
}
