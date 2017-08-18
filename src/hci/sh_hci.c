#include "shell.h"

t_token		*sh_hci(t_tc tc)
{
	t_line	*hist;
	t_token	*lexer;
//	char	*str;//tmp
	int		failure;

	(void)tc;
	lexer = NULL;///////
	failure = 0;
//	if (tc.on)
//	{
		if (!(hist = sh_hist_read()))
			failure = ft_error("Warning", "An error occured while preparing history", "you will be redirect to basic edition");
/*		else
		{
			str = sh_raw_edit(hist, tc);
			sh_hist_del(&hist);
		}
	}
	if (!tc.on || failure)
		str = sh_cooked_edit();
	if (str == NULL)
	{
		ft_error("retour null", NULL, NULL);
		return (NULL);
	}
*/	return (lexer);
}

/*
	if (!tc.on)
		str = sh_cooked_edit();//secu
	else
	{
		if (!(hist = sh_hist_read()))
		{
			ft_error(HIST_FILE, "Unable to get history.", NULL);
			return (NULL);
		}
		str = sh_raw_edit(hist, tc);//secu
		sh_hist_del(&hist);
	}
	if (str == NULL)
	{
		ft_error("retour null", NULL, NULL);
		return (NULL);
	}
	return (lexer);
}
*/
