#include "shell.h"

char	*sh_del_char(char *str)
{
	char	*new;

	new = NULL;
	if (str)
		new = ft_strndup(str, ft_strlen(str) - 1);
	free(str);
	return (new);
}

char	*sh_ins_char(char *str, char c)
{
	char	*new;
	int		i;

	i = 0;
	if (!str)
		return (new = ft_strdup(&c));
	while (str[i])
		i++;
	if (!(new = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	new[i] = c;
	new[++i] = '\0';
	return (new);
}

void	sh_i_prompt(char *str, t_tc *tc, int mode)
{
	if (mode == 0)
		ft_putstr("\r(reverse-i-search)'");
	else
		ft_putstr("\r(forward-i-search)'");
	tputs(tc->ce, 0, termput);
	ft_putstr(str);
	ft_putstr("\': ");
}
