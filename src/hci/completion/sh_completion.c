#include "shell.h"

static int	sh_cmp_init(char *str, size_t cur, char **lexeme, int *status)
{
	size_t	i[2];
	int		status;

	ft_bzero(i);
	while (i[0] < cur)
	{
		while (i[0] < cur && str[i[0] + i[1]] && !sh_metachar(str[i[0] + i[1]]))
			i[1]++;
		if (i[0] + i[1] == cur)
		{
			if (!(*lexeme = ft_strsub(str, i[0], i[1])))
				return (-1);
			return (0);
		}
		if (sh_rdir_op(str + i[0] + i[1]))
			*status = ARG;
		else if (sh_ctrl_op(str + i[0] + i[1]))
			*status = CMD;
		i[0] += i[1];
	}
	return (0);
}
