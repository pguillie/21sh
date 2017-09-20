/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:01:16 by pbourlet          #+#    #+#             */
/*   Updated: 2017/09/20 16:18:53 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "shell.h"
# include <signal.h>
# include <errno.h>

int		g_signal;

void	sh_catch_signals(void);
void	sh_dfl_sig(void);

#endif
