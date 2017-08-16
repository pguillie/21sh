/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 11:48:23 by pbourlet          #+#    #+#             */
/*   Updated: 2017/06/26 13:21:59 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *src, size_t size_src, size_t size_dest,
			size_t elem_size)
{
	void	*dest;

	if (!(dest = ft_memalloc((size_dest) * elem_size)))
		return (NULL);
	if (src)
	{
		ft_memcpy(dest, src, MIN(size_src, size_dest) * elem_size);
		ft_memdel(&src);
	}
	return (dest);
}
