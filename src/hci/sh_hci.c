#include "shell.h"

t_token		*sh_hci(t_tc tc)
{
	t_line	*hist;
	t_token	*lexer;
	char	*last;
	char	*str;//tmp
	int		failure;

	(void)tc;
	str = NULL;
	lexer = NULL;///////
	failure = 0;
	if (tc.on)
	{
		if (!(hist = sh_hist_read()))
			failure = ft_error("Warning", "An error occured while preparing history", "you will be redirect to basic edition");
		else
		{
			last = hist->prev ? ft_strjoin(hist->prev->str, "\n") : NULL;
			str = ft_strdup(sh_raw_edit(hist, last, tc));
			if (last)
				ft_strdel(&last);
			sh_hist_del(&hist);
		}
	}
	if (!tc.on || failure)
		failure = 1;//str = sh_cooked_edit();
	if (str == NULL)
	{
		ft_error("retour null", NULL, NULL);
		return (NULL);
	}
	return (lexer);
}
