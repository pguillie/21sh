#include "shell.h"

int		sh_prompt_conv(char c)
{
	if (c == 'u')
		return (sh_prompt_user());
	if (c == 'h')
		return (sh_prompt_host());
	if (c == 'w')
		return (sh_prompt_workdir());
	if (c == '$')
		return (sh_prompt_dollar());
	return (0);
}
