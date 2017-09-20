/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_crl_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:08:57 by pbourlet          #+#    #+#             */
/*   Updated: 2017/09/20 15:47:38 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_ctrl_d(t_line **line, t_coord **coord, t_tc *tc, char *save)
{
	int ret;

	ret = 0;
	if (!save && (*line)->str[0] == 0)
	{
		ft_putchar('\n');
		return (EOT);
	}
	if ((*line)->cur != (*line)->used)
		ret = sh_del_r(*line, coord, *tc);
	return (ret);
}
