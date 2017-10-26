#include "shell.h"

static int	sh_cmp_init(char *str, size_t cur, char **lexeme, int status)
{
	size_t	i[2];

	ft_bzero(i);
	while (str[i[0]])
	{
		while (str[i[0] + i[1]] && !sh_metachar(str[i[0] + i[1]]))
			i[1]++;
		if ()
		
	}
}

int			sh_completion(t_line *line)
{
	
}
