#include "shell.h"

static void	sig_handler(int sig)
{
	g_signal = sig;
	ft_putchar('\n');
}

void		sh_catch_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &sig_handler;
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		ft_error("Signal", "SIGINT", "Impossible to catch");
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
}
