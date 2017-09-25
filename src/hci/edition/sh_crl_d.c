/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_crl_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 15:08:57 by pbourlet          #+#    #+#             */
/*   Updated: 2017/09/25 11:37:06 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_ctrl_d(t_line *line, t_coord **coord, t_tc tc, char *save)
{
	if (line->str[line->cur])
		return (sh_del_r(line, coord, tc));
	else if (line->cur == 0 && !save)
		return (EOT);
	return (0);
}
