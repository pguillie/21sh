/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_host.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:00:15 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/25 18:00:16 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_host(char buff[], int *b, char h)
{
	char	host[128];
	int		i;
	int		len;

	len = 0;
	if (gethostname(host, 128) == 0)
	{
		i = 0;
		while (host[i])
		{
			if (host[i] == '.' && h == 'h')
				break ;
			len = (host[i] == '\n' ? 0 : len + 1);
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = host[i++];
		}
	}
	return (len);
}
