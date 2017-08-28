#include "shell.h"

int		sh_prompt_user(void)
{
	char	*user;

	user = getenv("LOGNAME");
	ft_putstr(user);
	return (ft_strlen(user));
}
