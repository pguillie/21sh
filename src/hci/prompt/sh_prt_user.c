#include "shell.h"

int		sh_prt_user(void)
{
	char	*user;

	user = getenv("LOGNAME");
	ft_putstr(user);
	return (ft_strlen(user));
}
