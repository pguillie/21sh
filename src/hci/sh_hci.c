#include "shell.h"

static int	sh_hci_raw(t_token **lexer, t_tc tc)
{
	t_line	*hist;
	char	*last;
	int		success;

	if (!(hist = sh_hist_read()))
	{
		return (ft_error("Warning",
				"An error occured while preparing history",
				"you will be redirect to basic edition"));
	}
	last = hist->up ? ft_strjoin(hist->up->str, "\n") : NULL;
	success = sh_raw_edit(hist, last, lexer, tc);
	last ? ft_strdel(&last) : 0;
	if (success < 0)
		return (-1);
	if (success > 0)
	{
		return (ft_error("Warning",
				"An error occured while preparing history",
				"you will be redirect to basic edition"));
	}
	sh_hist_del(&hist);
	return (0);
}

t_token		*sh_hci(t_tc tc)
{
	t_token	*lexer;
	int		failure;

	lexer = NULL;
	if (tc.on)
		if ((failure = sh_hci_raw(&lexer, tc)) < 0)
			ft_error("Severe error occured while getting input", NULL, NULL);
	if (!tc.on || failure == 1)
		if (sh_ckd_edit(&lexer))
			ft_error("Severe error occured while getting input", NULL, NULL);
	return (lexer);
}
