/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flush_buff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:06:40 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/25 18:06:40 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_flush_buff(char *buff, size_t size)
{
	size_t	i;

	write(1, buff, size);
	i = 0;
	while (i < size)
		buff[i++] = '\0';
	return (0);
}
