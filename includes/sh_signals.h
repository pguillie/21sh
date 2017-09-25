#ifndef SH_SIGNALS_H
# define SH_SIGNALS_H

# include "shell.h"
# include <signal.h>
# include <errno.h>

int		g_signal;

void	sh_catch_signals(void);
void	sh_dfl_sig(void);

#endif
