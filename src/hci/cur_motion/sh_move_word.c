#include "shell.h"

size_t	sh_move_word(long input, t_line *line)
{
	size_t	ret;

	ret = line->cur;
	while (line->str[ret - (input == K_C_LEFT ? 1 : 0)]
			&& !ft_isalnum(line->str[ret - (input == K_C_LEFT ? 1 : 0)]))
		ret += input == K_C_RIGHT ? 1 : -1;
	while (ft_isalnum(line->str[ret - (input == K_C_LEFT ? 1 : 0)]))
		ret += input == K_C_RIGHT ? 1 : -1;
	return (ret);
}
