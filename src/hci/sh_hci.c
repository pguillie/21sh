#include "shell.h"

int		sh_hci(t_tc *tc, t_token **lexer)
{
	t_line	*hist;
	char	*last;
	int		ret;

	if (!(hist = sh_hist_read()))
	{
		return (ft_error("\nSevere error occured while getting input",
					NULL, NULL));
	}
	last = hist->up ? ft_strjoin(hist->up->str, "\n") : NULL;
	ret = sh_edit(hist, last, lexer, tc);
	last ? ft_strdel(&last) : 0;
	if (ret < 0)
	{
		return (ft_error("\nSevere error occured while getting input",
					NULL, NULL));
	}
	if (ret & SYN_ERR)
		sh_token_del(lexer);
	sh_hist_del(&hist);
	return (0);
}
