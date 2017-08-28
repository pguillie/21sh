#include "shell.h"

static int	sh_cat_sep(char *str)
{
	if (ft_strequ(str, "||") || ft_strequ(str, "&&"))
		return (ANDOR);
	if (ft_strequ(str, ";") || ft_strequ(str, "&"))
		return (ESPERCOLON);
	if (ft_strequ(str, "|"))
		return (PIPE);
	if (ft_strequ(str, "\n"))
		return (NEWLINE);
	return (0);
}

int			sh_category(char *str)
{
	static int	status = CMD;
	int			sep;

	if ((sep = sh_cat_sep(str)))
	{
		status = CMD;
		return (sep);
	}
	if (sh_rdir_op(str))
		return (REDIRECTION);
	if (status == CMD)
		return (status--);
	if (status == OPT)
	{
		if (ft_strnequ(str, "--", 2))
			return (status--);
		if (str[0] == '-')
			return (status);
		else
			status = ARG;
	}
	return (status);
}
