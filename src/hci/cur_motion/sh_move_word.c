#include "shell.h"

size_t	sh_move_word(int move, t_line *line)
{
	size_t	ret;

	ret = line->cur;
	while (line->str[ret - (move == LEFT ? 1 : 0)]
			&& !ft_isalnum(line->str[ret - (move == LEFT ? 1 : 0)]))
		ret += move == RIGHT ? 1 : -1;
	while (ft_isalnum(line->str[ret - (move == LEFT ? 1 : 0)]))
		ret += move == RIGHT ? 1 : -1;
	return (ret);
}
