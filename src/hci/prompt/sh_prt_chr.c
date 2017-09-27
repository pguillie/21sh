/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_chr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 17:59:56 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/25 17:59:57 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	sh_prt_chr(char buff[], int *b, char c, int *len)
{
	if (*b == PRT_SIZE)
		*b = ft_flush_buff(buff, PRT_SIZE);
	if (c == 'a')
	{
		buff[*b] = '\a';
		*len += 1;
	}
	else
	{
		if (c == 'n')
			buff[*b] = '\n';
		else if (c == 'r')
			buff[*b] = '\r';
		*len = 0;
	}
	*b += 1;
}
