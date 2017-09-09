/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 13:58:47 by pbourlet          #+#    #+#             */
/*   Updated: 2017/09/09 12:09:34 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static	char	*ft_append(char *str, int fd, int *eof)
{
	char	*buffer;
	char	*tmp;
	int		ret;
	int		t;

	t = 0;
	if (!(buffer = ft_strnew(BUFF_SIZE)))
		return (NULL);
	if (*str == '\n')
		*eof = 1;
	while (!t || !(ft_strchr(str, '\n') || *eof))
	{
		if ((ret = read(fd, buffer, BUFF_SIZE)) == -1)
			return (NULL);
		t = 1;
		if (ret < BUFF_SIZE)
			*eof = 1;
		tmp = str;
		str = ft_strjoin(str, buffer);
		ft_strdel(&tmp);
		ft_strclr(buffer);
	}
	free(buffer);
	return (str);
}

int				get_next_line(const int fd, char **line)
{
	static char		*str[500];
	int				i;
	int				eof;

	i = 0;
	eof = 0;
	if (fd < 0 || !line || (str[fd] ? 0 : !(str[fd] = ft_strnew(BUFF_SIZE))))
		return (-1);
	if ((str[fd] = ft_append(str[fd], fd, &eof)) == NULL)
		return (-1);
	if (str[fd][0] == '\0' && eof)
	{
		ft_strdel(&str[fd]);
		free(str[fd]);
		return (0);
	}
	while (str[fd][i] && str[fd][i] != '\n')
		i++;
	*line = ft_strsub(str[fd], 0, i);
	if (str[fd][i])
		ft_memmove(str[fd], str[fd] + i + 1,
				ft_strlen(str[fd] + i + (str[fd][i] ? 1 : 0) - 1));
	else
		str[fd][0] = '\0';
	return (1);
}
