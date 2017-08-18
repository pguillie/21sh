#include "shell.h"

int		sh_init_termcaps(t_tc *init)
{
	char	*termtype;
	int		success;

	if (!(termtype = getenv("TERM")))
		return (ft_error("`TERM' environment variable not found", NULL, NULL));
	success = tgetent(init->data, termtype);
	if (success < 0)
		return (ft_error("Could not access the termcap data base", NULL, NULL));
	else if (success == 0)
		return (ft_error(termtype, "Terminal type not defined", NULL));
	ft_bzero(init->buff, 2048);
	if (!(init->nd = tgetstr("nd", (char**)&(init->buff))))
		return (ft_error("nd", "termcap not provided by terminal", NULL));
	if (!(init->le = tgetstr("le", (char**)&(init->buff))))
		return (ft_error("le", "termcap not provided by terminal", NULL));
	return (0);
}
