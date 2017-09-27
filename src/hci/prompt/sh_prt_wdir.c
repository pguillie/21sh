/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_prt_wdir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/25 18:01:10 by pguillie          #+#    #+#             */
/*   Updated: 2017/09/27 18:50:20 by pguillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

static char	*sh_prt_home(char *pwd, char *tmp)
{
	char	*home;
	int		i;

	*tmp = pwd[0];
	if (pwd && (home = getenv("HOME")) && home[0])
	{
		i = 0;
		while (home[i] && home[i] == pwd[i])
			i++;
		if (i && !home[i] && home[i] != '/'
			&& (pwd[i] == '\0' || pwd[i] == '/'))
		{
			*tmp = pwd[i - 1];
			pwd[i - 1] = '~';
			return (pwd + i - 1);
		}
	}
	return (pwd);
}

static int	sh_prt_dirtrim(char *pwd, char w)
{
	int		dirtrim;
	int		i;

	dirtrim = (w == 'W' ? 1 : PROMPT_DIRTRIM);
	i = 0;
	if (dirtrim)
	{
		while (pwd[i + 1])
			i += 1;
		while (i && pwd[i] == '/')
			i -= 1;
		while (i && dirtrim)
		{
			if (pwd[i] == '/' && ((dirtrim -= 1) || 1))
				while (dirtrim && i && pwd[i] == '/')
					i -= 1;
			else
				i -= 1;
		}
	}
	if (i && pwd[i] == '/' && w == 'W')
		i += 1;
	return (i);
}

static int	sh_prt_wfill(char buff[], int *b, char *src, int len)
{
	int		i;

	i = 0;
	while (src[i])
	{
		len = (src[i] == '\n' ? 0 : len + 1);
		if (*b == PRT_SIZE)
			*b = ft_flush_buff(buff, PRT_SIZE);
		buff[(*b)++] = src[i++];
	}
	return (len);
}

int			sh_prt_wdir(char buff[], int *b, char w)
{
	char	*pwd;
	char	tmp;
	int		pos;
	int		len;

	len = 0;
	if ((pwd = sh_prt_home(getenv("PWD"), &tmp)))
	{
		pos = sh_prt_dirtrim(pwd, w);
		if (w == 'w' && pos)
		{
			if (pwd[0] == '~' && pos == 1)
				len = sh_prt_wfill(buff, b, "~", len);
			else if (pwd[0] == '~')
				len = sh_prt_wfill(buff, b, "~/...", len);
			else
				len = sh_prt_wfill(buff, b, "...", len);
		}
		len = sh_prt_wfill(buff, b, pwd + pos, len);
		pwd[0] = tmp;
	}
	return (len);
}
