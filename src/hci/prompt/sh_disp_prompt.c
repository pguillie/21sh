#include "shell.h"

void		sh_disp_prompt(char buff[], size_t *j)
{
	ft_putstr(buff);
	ft_strclr(buff);
	*j = 0;
}
