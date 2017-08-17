/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 16:06:05 by pguillie          #+#    #+#             */
/*   Updated: 2017/08/11 16:14:14 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char	*sh_getenv(char *name, char *env[])
{
	size_t		i;

	if (!env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strnequ(env[i], name, ft_strlen(name))
				&& ft_strcmp(env[i], name) == '=')
			return (env[i] + ft_strlen(name) + 1);
		i++;
	}
	return (NULL);
}
