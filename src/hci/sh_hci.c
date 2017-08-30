#include "shell.h"

void	displex(t_token *lexer)
{
	ft_putendl("\n=== DISPLEX ===\n");
	while (lexer)
	{
		ft_printf("category:%2d -- lexeme:%s\n", lexer->category, lexer->lexeme);
		lexer = lexer->next;
	}
}

void disphist(t_line *line)
{
	while (line)
	{
		ft_printf("hist: '%s'\n", line->str);
		line = line->prev;
	}
}

t_token		*sh_hci(t_tc tc)
{
	t_line	*hist;
	t_token	*lexer;
	char	*last;
	int		failure;

	lexer = NULL;
	failure = 0;
	if (tc.on)
	{
		if (!(hist = sh_hist_read()))
			failure = ft_error("Warning", "An error occured while preparing history", "you will be redirect to basic edition");
		else
		{
	//		disphist(hist);
			last = hist->prev ? ft_strjoin(hist->prev->str, "\n") : NULL;
			sh_raw_edit(hist, last, &lexer, tc);
			if (last)
				ft_strdel(&last);
			sh_hist_del(&hist);
		}
	}
	if (!tc.on || failure)
		sh_ckd_edit(&lexer);
	displex(lexer);
	return (lexer);
}
