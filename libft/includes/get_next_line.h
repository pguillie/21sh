/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 19:16:05 by pguillie          #+#    #+#             */
/*   Updated: 2017/08/18 15:51:55 by lcordier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define BUFF_SIZE 10

typedef struct	s_gnl
{
	char		*str[500];
	char		buff[BUFF_SIZE + 1];
	char		*tmp;
	int			i;
	int			ret;
}				t_gnl;

int				get_next_line(int fd, char **line);

#endif
