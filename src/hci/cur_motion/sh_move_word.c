#include "shell.h"

int		sh_move_word_r(t_line *line)
{
	size_t	pos;

	pos = line->cur;
	while (line->str[pos] && !ft_isalnum(line->str[pos]))
		pos += 1;
	while (ft_isalnum(line->str[pos]))
		pos += 1;
	return (pos);
}

int		sh_move_word_l(t_line *line)
{
	size_t	pos;

	pos = line->cur - 1;
	while (line->str[pos] && !ft_isalnum(line->str[pos]))
		pos -= 1;
	while (ft_isalnum(line->str[pos]))
		pos -= 1;
	return (pos + 1);
}
