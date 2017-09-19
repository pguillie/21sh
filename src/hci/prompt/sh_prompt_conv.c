#include "shell.h"

static int	sh_prt_conv_c(char c)
{
	if (c == 'a')
		ft_putchar('\a');
	else if (c == 'n')
		ft_putchar('\n');
	else if (c == 'r')
		ft_putchar('\r');
	else if (c == '\\')
		ft_putchar('\\');
	else
		return (0);
	return (1);
}

static int	sh_prt_esc(void)
{
	ft_putchar(27);
	return (0);
}

int			sh_prompt_conv(char c)
{
	if (sh_prt_conv_c(c))
		return (1);
	if (c == 'd')
		return (sh_prt_date());
//	if (c == 'D')
//		;
	if (c == 'e')
		return (sh_prt_esc());
	if (c == 'h' || c == 'H')
		return (sh_prt_host(c));
//	if (c == 'j')
//		;
//	if (c == 'l')
//		;
//	if (c == 's')
//		;
	if (c == 't' || c == 'T' || c == '@' || c == 'A')
		return (sh_prt_time(c));
	if (c == 'u')
		return (sh_prt_user());
//	if (c == 'v' || c == 'V')
//		;
	if (c == 'w' || c == 'W')
		return (sh_prt_wdir(c));
//	if (c == '!')
//		;
//	if (c == '#')
//		;
	if (c == '$')
		return (sh_prt_end());
	return (0);
}
