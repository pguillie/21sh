#include "shell.h"

static int	sh_tab_norme(char *str, size_t *i, int *status, int cmd)
{
	if ((i[1] = sh_rdir_op(str + i[0])))
		*status = ARG;
	else if ((i[1] = sh_ctrl_op(str + i[0])))
	{
		*status = CMD;
		cmd = 0;
	}
	else
	{
		i[0] += 1;
		if (cmd == 1)
			*status = ARG;
	}
	return (cmd);
}

int			sh_tab_init(char *str, size_t cur, char **lexeme, int *status)
{
	size_t	i[2];
	int		cmd;

	i[0] = 0;
	cmd = 0;
	while (i[0] < cur)
	{
		i[1] = 0;
		if (!sh_metachar(str[i[0]]))
		{
			i[1] = sh_lex_word(str + i[0]);
			if (i[0] + i[1] >= cur)
				if (!(*lexeme = ft_strsub(str, i[0],
								i[0] + i[1] > cur ? cur - i[0] : i[1])))
					return (-1);
			if (*status == CMD)
				cmd = 1;
		}
		else
			cmd = sh_tab_norme(str, i, status, cmd);
		if (i[1])
			i[0] += i[1];
	}
	return ((!*lexeme && !(*lexeme = ft_strdup(""))) ? -1 : 0);
}
