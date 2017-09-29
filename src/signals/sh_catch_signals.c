#include "shell.h"

static void	sig_handler(int sig)
{
	g_signal = sig;
}

void		sh_catch_signals(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_handler = &sig_handler;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGWINCH, &sa, NULL);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, SIG_IGN);
	signal(SIGCONT, SIG_IGN);
}
