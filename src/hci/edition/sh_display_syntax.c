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

static void	sh_disp_geteof(char *str, int *hd, size_t eof[2], int pos)
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

static int	sh_disp_hd(t_line *line, size_t i, int *hd, t_tc tc)
{
	int		j;
	size_t	eof[2];
	size_t	lim[2];

	ft_memset(eof, 0, sizeof(int) * 2);
	sh_disp_geteof(line->str, hd, eof, i);
	j = 0;
	lim[0] = i;
	lim[1] = 0;
	ft_putstr_fd(C_HEREDOC, 0);
	while (line->str[i + j])
	{
		if (line->str[lim[0] + lim[1]] == '\n')
		{
			if (lim[1] == eof[1]
					&& ft_strnequ(line->str + lim[0], line->str + eof[0], eof[1]))
				return (j);
			lim[0] += lim[1] + 1;
			lim[1] = 0;
		}
		else
			lim[1] += 1;
		sh_disp_part(line, tc, i + j++, 1);		/*
		old: 	ft_putchar_fd(str[i + j++], 0);	*/
	}
	return (j + 1);
}

static void	sh_disp_norme(t_line *line, size_t i[2], int status[2], int *hd, t_tc tc)
{
	if ((i[1] = sh_ctrl_op(line->str + i[0])))
	{
		status[0] = CMD;
		ft_putstr_fd(i[1] == 1 && line->str[i[0]] == '|' ? C_PIPE : C_SEPAR, 0);
		write(0, line->str + i[0], i[1]);
		if (i[1] == 1 && line->str[i[0]] == '\n' && *hd > 0)
		{
			ft_putstr_fd(C_EOC, 0);
			i[1] += sh_disp_hd(line, i[0] + i[1], hd, tc);
		}
	}
	else
		sh_disp_part(line, tc, i[0], i[1]);			/*
		old:	write(0, str + i[0], (i[1] = 1));	*/
}

void		sh_display_syntax(t_line *line, t_tc tc)
{
	size_t	i[2];
	int		status[2];
	int		hd;

	i[0] = 0;
	status[0] = CMD;
	status[1] = 0;
	hd = 0;
	while (line->str[i[0]])
	{
		i[1] = 0;
		if (!sh_metachar(line->str[i[0]]))
			i[1] = sh_disp_word(line->str + i[0], status, &hd);
		else if ((i[1] = sh_rdir_op(line->str + i[0])))
		{
			status[1] = (i[1] == 2 && ft_strnequ(line->str + i[0], "<<", 2)) ? 2 : 1;
			ft_putstr_fd(C_REDIR, 0);
			sh_disp_part(line, tc, i[0], i[1]);	/*
			old:	write(0, str + i[0], i[1]);	*/
		}
		else
			sh_disp_norme(line, i, status, &hd, tc);
		ft_putstr_fd(C_EOC, 0);
		i[0] += i[1];
	}
}
