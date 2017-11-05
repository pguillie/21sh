#include "shell.h"

static int	sh_disp_word(char *str, int *status, int *hd)
{
	int		len;

	len = sh_lex_word(str);
	if (status[1] || (len == 1 && str[0] >= '0' && str[0] <= '9'
				&& str[1] != '&' && sh_rdir_op(str + 1)))
	{
		if (status[1] == 2 && *hd <= 0)
			*hd = ABS(*hd) + 1;
		ft_putstr_fd(status[1] > 1 ? C_HDMATCH : C_FILDES, 0);
	}
	else if (status[0] == CMD)
	{
		ft_putstr_fd(C_CMD, 0);
		status[0]--;
	}
	else if (status[0] == OPT && str[0] == '-'
			&& !ft_strnequ(str, "--", len > 2 ? len : 2))
		ft_putstr_fd(C_OPT, 0);
	else if ((status[0] = ARG) || 1)
		ft_putstr_fd(C_ARG, 0);
	write(0, str, len);
	status[1] = 0;
	return (len);
}

static void	sh_disp_geteof(char *str, int *hd, int eof[2], int pos)
{
	int		i[2];
	int		c;

	c = 0;
	i[0] = 0;
	while (str[i[0]] && i[0] < pos)
	{
		if (!sh_metachar(str[i[0]]))
		{
			i[1] = sh_lex_word(str + i[0]);
			if (c == *hd && eof[1] == 0)
			{
				eof[0] = i[0];
				eof[1] = i[1];
			}
		}
		else if ((i[1] = sh_rdir_op(str + i[0])) == 2
				&& ft_strnequ(str + i[0], "<<", 2))
			c += 1;
		else
			i[1] = 1;
		i[0] += i[1];
	}
	*hd = (c > *hd) ? *hd + 1 : -(*hd);
}

static int	sh_disp_hd(char *str, int i, int *hd)
{
	int		j;
	int		eof[2];
	int		line[2];

	ft_memset(eof, 0, sizeof(int) * 2);
	sh_disp_geteof(str, hd, eof, i);
	j = 0;
	line[0] = i;
	line[1] = 0;
	ft_putstr_fd(C_HEREDOC, 0);
	while (str[i + j])
	{
		if (str[line[0] + line[1]] == '\n')
		{
			if (line[1] == eof[1]
					&& ft_strnequ(str + line[0], str + eof[0], eof[1]))
				return (j);
			line[0] += line[1] + 1;
			line[1] = 0;
		}
		else
			line[1] += 1;
		ft_putchar_fd(str[i + j++], 0);
	}
	return (j + 1);
}

static void	sh_disp_norme(char *str, int i[2], int status[2], int *hd)
{
	if ((i[1] = sh_ctrl_op(str + i[0])))
	{
		status[0] = CMD;
		ft_putstr_fd(i[1] == 1 && str[i[0]] == '|' ? C_PIPE : C_SEPAR, 0);
		write(0, str + i[0], i[1]);
		if (i[1] == 1 && str[i[0]] == '\n' && *hd > 0)
		{
			ft_putstr_fd(C_EOC, 0);
			i[1] += sh_disp_hd(str, i[0] + i[1], hd);
		}
	}
	else
		write(0, str + i[0], (i[1] = 1));
}

void		sh_display_syntax(char *str)
{
	int		i[2];
	int		status[2];
	int		hd;

	i[0] = 0;
	status[0] = CMD;
	status[1] = 0;
	hd = 0;
	while (str[i[0]])
	{
		i[1] = 0;
		if (!sh_metachar(str[i[0]]))
			i[1] = sh_disp_word(str + i[0], status, &hd);
		else if ((i[1] = sh_rdir_op(str + i[0])))
		{
			status[1] = (i[1] == 2 && ft_strnequ(str + i[0], "<<", 2)) ? 2 : 1;
			ft_putstr_fd(C_REDIR, 0);
			write(0, str + i[0], i[1]);
		}
		else
			sh_disp_norme(str, i, status, &hd);
		ft_putstr_fd(C_EOC, 0);
		i[0] += i[1];
	}
}
