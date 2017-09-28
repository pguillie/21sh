/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_strftime.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:00:33 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/25 18:00:33 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int		sh_prt_strftime(char buff[], int *b, char *format, struct tm *tm)
{
	char	date[128];
	int		i;
	int		len;

	len = 0;
	if (strftime(date, 128, format, tm) > 0)
	{
		i = 0;
		while (date[i])
		{
			len = (date[i] == '\n' ? 0 : len + 1);
			if (*b == PRT_SIZE)
				*b = ft_flush_buff(buff, PRT_SIZE);
			buff[(*b)++] = date[i++];
		}
	}
	return (len);
}
