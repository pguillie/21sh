/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtab_disp.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 12:59:46 by pguillie          #+#    #+#             */
/*   Updated: 2017/07/11 19:47:18 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strtab_disp_col(char **tab, size_t size, size_t len, size_t col)
{
	char	space[1024];
	size_t	i[3];
	size_t	pos;

	pos = 1;
	ft_bzero(i, 3 * sizeof(size_t));
	ft_memset(space, ' ', 1024);
	while (i[2] < size)
	{
		ft_putstr(tab[i[0]]);
		if (++pos > col || i[0] + (size - 1) / col + 1 >= size)
		{
			ft_putstr("\r\n");
			pos = 1;
			i[0] = ++i[1];
		}
		else
		{
			write(1, space, len - ft_strlen(tab[i[0]]));
			i[0] += (size - 1) / col + 1;
		}
		i[2]++;
	}
}

void		ft_strtab_disp(char **tab)
{
	struct winsize	w;
	size_t			size;
	size_t			len;
	size_t			row;

	if (tab && *tab)
	{
		len = 0;
		if (ioctl(0, TIOCGWINSZ, &w) < 0)
		{
			while (tab[len])
				ft_putendl(tab[len++]);
		}
		else
		{
			size = 0;
			while (tab[size])
			{
				if (ft_strlen(tab[size]) >= len)
					len = ft_strlen(tab[size]) + 1;
				size++;
			}
			row = w.ws_col / len ? (size - 1) / (w.ws_col / len) + 1 : size;
			ft_strtab_disp_col(tab, size, len, (size - 1) / row + 1);
		}
	}
}
