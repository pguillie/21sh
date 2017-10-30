/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdescamp <mdescamp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:01:13 by mdescamp          #+#    #+#             */
/*   Updated: 2017/10/30 16:02:51 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrstr(const char *haystack, const char *needle)
{
	int		i;

	if (needle[0] == '\0')
		return ((char*)haystack);
	i = ft_strlen(haystack);
	while (i >= 0)
	{
		if (!(ft_strncmp(haystack + i, needle, ft_strlen(needle))))
			return ((char*)haystack + i);
		i--;
	}
	return (NULL);
}
