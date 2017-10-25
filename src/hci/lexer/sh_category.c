#include "shell.h"

static int	sh_cat_op(char *str, int status[3])
{
	if (ft_strnequ(str, "||", 2) || ft_strnequ(str, "&&", 2))
		return (ANDOR);
	if (ft_strnequ(str, ";", 1) || ft_strnequ(str, "&", 1))
		return (ESPERCOLON);
	if (ft_strnequ(str, "|", 1))
		return (PIPE);
	if (ft_strnequ(str, "\n", 1))
	{
		status[2] = 1;
		return (NEWLINE);
	}
	return (0);
}

static int	sh_cat_coa(char *str, int i[2], int status[3])
{
	status[1] = 0;
	if (status[0] == CMD)
		return (status[0]--);
	if (status[0] == OPT)
	{
		if (ft_strnequ(str + i[0], "--", i[1] > 2 ? i[1] : 2))
			return (status[0]--);
		if (str[i[0]] == '-')
			return (status[0]);
		else
			status[0] = ARG;
	}
	return (status[0]);
}

int			sh_category(char *str, int i[2], int status[3])
{
	if (sh_cat_op(str + i[0], status))
	{
		status[0] = CMD;
		return (sh_cat_op(str + i[0], status));
	}
	status[2] = 0;
	if ((i[1] == 1 && str[i[0]] >= '0' && str[i[0]] <= '9'
				&& sh_rdir_op(str + i[0] + i[1]))
			|| (str[i[0]] != '-' && status[1]))
		return ((status[1] == 2 ? HEREDOC : FILDES) + (status[1] = 0));
	if (sh_rdir_op(str + i[0]))
	{
		status[1] = (i[1] == 2 && ft_strnequ(str + i[0], "<<", i[1])) ? 2 : 1;
		return (REDIRECTION);
	}
	return (sh_cat_coa(str, i, status));
}
