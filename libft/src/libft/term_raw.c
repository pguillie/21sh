/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_raw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pguillie <pguillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 16:35:52 by pguillie          #+#    #+#             */
/*   Updated: 2017/08/22 16:45:18 by mdescamp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		term_raw(t_termios *get, int vtime, int vmin)
{
	t_termios	set;

	if (tcgetattr(0, get) < 0)
		return (ft_error("Unable to get the termios structure", NULL, NULL));
	set = *get;
	set.c_lflag &= ~(ECHO | ICANON);
	set.c_cc[VTIME] = vtime;
	set.c_cc[VMIN] = vmin;
	if (tcsetattr(0, TCSANOW, &set) < 0)
		return (ft_error("Unable to set raw termios structure", NULL, NULL));
	return (0);
}
