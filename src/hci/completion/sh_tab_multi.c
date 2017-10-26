/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_tab_multi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:55:08 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/26 16:59:20 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static int	sh_norminette(t_line *line, t_coord **coord, t_tc tc, char *array[])
{
	size_t	size;
	int		disp;
	char	ans;

	size = 0;
	while (array[size])
		size += 1;
	sh_move_cur(line->cur, line->used, *coord, tc);
	if ((disp = 1) && size > 100)
	{
		ft_printf("\nDisplay all %d possibilities? (y or n)", size);
		ans = 0;
		while (ans != 'y' && ans != 'n' && ans != 127 && ans != ' '
				&& g_sig != SIGINT)
			read(0, &ans, 1);
		if (ans == 'n' || ans == 127)
			disp = 0;
	}
	g_sig != SIGINT ? write(1, "\n", 1) : 0;
	if (disp && g_sig != SIGINT)
	{
		array = ft_strtab_sort(array);
		ft_strtab_disp(array);
	}
	return (DISP_FULL);
}

int			sh_tab_multi(t_line *line, t_coord **coord, t_tc tc, char *array[])
{
	char	occ[PATH_SIZE];
	size_t	i;
	size_t	j;

	ft_strncpy(occ, array[1], PATH_SIZE);
	i = 2;
	while (array[i] && occ[0])
	{
		j = 0;
		while (j < PATH_SIZE && occ[j] == array[i][j])
			j++;
		ft_strclr(occ + j);
		i += 1;
	}
	if (ft_strlen(occ) > ft_strlen(array[0]))
		return (sh_tab_comp(line, coord, tc, occ + ft_strlen(array[0])));
	else
		return (sh_norminette(line, coord, tc, array + 1));
}
