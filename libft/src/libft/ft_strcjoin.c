/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 12:11:15 by pguillie          #+#    #+#             */
/*   Updated: 2017/07/10 16:35:38 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcjoin(const char *s1, const char *s2, char c)
{
	char	*new;
	int		i[2];

	if (!s1 || !s2)
		return (ft_strjoin(s1, s2));
	if (!(new = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	i[0] = 0;
	i[1] = 0;
	if (s1)
		while (s1[i[1]])
			new[i[0]++] = s1[i[1]++];
	new[i[0]++] = c;
	i[1] = 0;
	if (s2)
		while (s2[i[1]])
			new[i[0]++] = s2[i[1]++];
	return (new);
}
