#include "shell.h"

void	sh_cmd_del(t_cmd **cmd)
{
	size_t	i;

	ft_strtabdel((*cmd)->av);
	i = 0;
	while (i < (*cmd)->redir->size)
	{
		ft_strdel(&((*cmd)->redir[i].type));
		ft_strdel(&((*cmd)->redir[i].right));
		i++;
	}
	ft_memdel((void**)&(*cmd)->redir);
	ft_memdel((void**)cmd);
}
