#include "shell.h"

int		sh_cut_w(t_line *line, t_coord **coord, t_tc *tc)
{
	size_t	i;
	char	*cpy;

	if (!line->str || line->cur == 0)
		return (0);
	i = sh_move_word_l(line);
	if (!tc->clipboard)
		cpy = ft_strnew(line->cur - i);
	else
		cpy = ft_strnew(line->cur - i + ft_strlen(tc->clipboard));
	ft_strncat(cpy, line->str + i, line->cur - i);
	tc->clipboard ? ft_strcat(cpy, tc->clipboard) : 0;
	ft_memmove(line->str + i, line->str + line->cur,
			ft_strlen(line->str + line->cur));
	ft_strclr(line->str + ft_strlen(line->str) - (line->cur - i));
	line->used -= line->cur - i;
	line->pos = i;
	line->cur = sh_move_cur(line->cur, line->pos, *coord, *tc);
	free(tc->clipboard);
	tc->clipboard = cpy;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc->prompt)))
		return (-1);
	return (DISP | LEXER);
}

int		sh_cut_u(t_line *line, t_coord **coord, t_tc *tc)
{
	size_t	i;
	size_t	j;
	char	*cpy;

	i = line->cur;
	j = ft_strlen(tc->clipboard);
	if (!line->str || line->cur == 0)
		return (0);
	if (!tc->clipboard)
		cpy = ft_strnew(line->cur + 1);
	else
		cpy = ft_strnew(ft_strlen(tc->clipboard) + line->cur);
	ft_strncat(cpy, line->str, i);
	tc->clipboard ? ft_strcat(cpy, tc->clipboard) : 0;
	ft_memmove(line->str, line->str + line->cur,
			ft_strlen(line->str + line->cur));
	ft_strclr(line->str + ft_strlen(line->str + line->cur));
	line->used -= line->cur;
	line->cur = sh_move_cur(line->cur, 0, *coord, *tc);
	line->pos = 0;
	free(tc->clipboard);
	tc->clipboard = cpy;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc->prompt)))
		return (-1);
	return (DISP | LEXER);
}

int		sh_cut_k(t_line *line, t_coord **coord, t_tc *tc)
{
	size_t	i;
	size_t	j;
	char	*cpy;

	i = line->cur;
	j = ft_strlen(tc->clipboard);
	if (!line->str || line->cur == line->used)
		return (0);
	if (!tc->clipboard)
		cpy = ft_strnew(j + line->used - line->cur + 1);
	else
	{
		cpy = ft_strnew(ft_strlen(tc->clipboard) + line->used - line->cur);
		ft_strcat(cpy, tc->clipboard);
	}
	while (i < line->used)
	{
		cpy[j++] = line->str[i];
		line->str[i++] = '\0';
	}
	line->used -= (line->used - line->cur);
	free(tc->clipboard);
	tc->clipboard = cpy;
	free(*coord);
	if (!(*coord = sh_create_coord(line, tc->prompt)))
		return (-1);
	return (DISP | LEXER);
}
