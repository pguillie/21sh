/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:30:32 by pguillie          #+#    #+#             */
/*   Updated: 2017/10/27 23:10:37 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *haystack, const char *needle)
{
	int		i;

	if (needle[0] == '\0')
		return ((char*)haystack);
	i = ft_strlen(haystack) - 1;
	while (i)
	{
		if (!(ft_strncmp(haystack + i, needle, ft_strlen(needle))))
			return ((char*)haystack + i);
		i--;
	}
	return (NULL);
}
