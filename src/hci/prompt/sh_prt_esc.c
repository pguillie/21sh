/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_esc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:00:06 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/27 18:56:03 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_esc(char buff[], int *b, char *ps)
{
	int		i;

	i = 1;
	if (*b == PRT_SIZE)
		*b = ft_flush_buff(buff, PRT_SIZE);
	buff[(*b)++] = 27;
	if (*b == PRT_SIZE)
		*b = ft_flush_buff(buff, PRT_SIZE);
	buff[*b] = ps[i++];
	if (buff[(*b)++] == '[')
	{
		while (ps[i] < '@' || ps[i] > '~')
		{
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = ps[i++];
		}
		if (*b == PRT_SIZE)
			*b = ft_flush_buff(buff, PRT_SIZE);
		buff[(*b)++] = ps[i++];
	}
	return (i);
}
