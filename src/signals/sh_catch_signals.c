/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_catch_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbourlet <pbourlet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:00:21 by pbourlet          #+#    #+#             */
/*   Updated: 2017/09/19 17:13:37 by pbourlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

static void	sig_handler(int sig)
{
	g_signal = sig;
	ft_putchar('\n');
}

void	sh_catch_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_error("Signal", "SIGINT", "Impossible to catch");
	if (sigaction(SIGCONT, &sa, NULL) == -1)
		ft_error("Signal", "SIGCONT", "Impossible to catch");
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
}
