/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 18:46:21 by pguillie          #+#    #+#             */
/*   Updated: 2017/08/31 11:15:43 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char *base, char const *to_app, char side)
{
	char	*new;

	if (side == 'l')
		new = ft_strjoin(to_app, base);
	if (side == 'r')
		new = ft_strjoin(base, to_app);
	base ? ft_strdel(&base) : 0;
	return (new);
}
