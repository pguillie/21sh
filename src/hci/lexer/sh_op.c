#include "shell.h"

int		sh_ctrl_op(char *str)
{
	if (ft_strnequ(str, ";;&", 3))
		return (3);
	if (ft_strnequ(str, "||", 2) || ft_strnequ(str, "&&", 2)
			|| ft_strnequ(str, ";;", 2) || ft_strnequ(str, ";&", 2)
			|| ft_strnequ(str, "|&", 2))
		return (2);
	if ((str[0] == '&' && str[1] != '>') || str[0] == ';' || str[0] == '|' || str[0] == '('
			|| str[0] == ')' || str[0] == '\n')
		return (1);
	return (0);
}

int		sh_rdir_op(char *str)
{
	if (ft_strnequ(str, "&>>", 3) || ft_strnequ(str, "<<<", 3))
		return (3);
	if (ft_strnequ(str, "&>", 2) || ft_strnequ(str, ">&", 2)
			|| ft_strnequ(str, ">|", 2) || ft_strnequ(str, ">>", 2)
			|| ft_strnequ(str, "<<", 2) || ft_strnequ(str, "<&", 2))
		return (2);
	if (str[0] == '<' || str[0] == '>')
		return (1);
	return (0);
}
