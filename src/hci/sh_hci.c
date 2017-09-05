#include "shell.h"

t_token		*sh_hci(t_tc *tc)
{
	t_token	*lexer;
	t_line	*hist;
	char	*last;
	int		failure;

	lexer = NULL;
	if (!(hist = sh_hist_read()))
	{
		ft_error("\nSevere error occured while getting input", NULL, NULL);
		return (NULL);
	}
	last = hist->up ? ft_strjoin(hist->up->str, "\n") : NULL;
	failure = sh_edit(hist, last, &lexer, tc);
	last ? ft_strdel(&last) : 0;
	if (failure < 0)
	{
		ft_error("\nSevere error occured while getting input", NULL, NULL);
		return (NULL);
	}
	sh_hist_del(&hist);
	return (lexer);
}
