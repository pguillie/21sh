#include "shell.h"

static char	*sh_exp_til_home(char *name, int len)
{
	struct passwd	*p;
	char			*home;
	char			tmp;

	home = NULL;
	if (!len)
	{
		home = getenv("HOME");
		if (!home && (p = getpwuid(getuid())))
			home = p->pw_dir;
	}
	else
	{
		tmp = name[len];
		name[len] = '\0';
		if ((p = getpwnam(name)))
			home = p->pw_dir;
		name[len] = tmp;
	}
	return (home);
}

static char	*sh_exp_til_fnd(char *lex, int *i)
{
	char	*new;
	char	*rplc;
	int		len;

	if (*i && (lex[*i - 1] != '=' && lex[*i - 1] != ':'))
		return (lex);
	len = 0;
	while (lex[*i + len] && lex[*i + len] != '/' && lex[*i + len] != ':')
		len += 1;
	if (len == 2 && ft_strnequ(lex + *i, "~+", 2))
		rplc = getenv("PWD");
	else if (len == 2 && ft_strnequ(lex + *i, "~-", 2))
		rplc = getenv("OLDPWD");
	else
		rplc = sh_exp_til_home(lex + *i + 1, len - 1);
	if (rplc && (new = ft_strnew(ft_strlen(lex) - len + ft_strlen(rplc))))
	{
		ft_strncpy(new, lex, *i);
		ft_strcat(new, rplc);
		ft_strcat(new, lex + *i + len);
		free(lex);
		lex = new;
	}
	return (lex);
}

char		*sh_exp_tilde(char *lex)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (lex[i])
	{
		if (lex[i] == '\\')
			i++;
		else if (lex[i] == quote)
			quote = 0;
		else if ((lex[i] == '\'' || lex[i] == '\"' || lex[i] == '`')
				&& !quote)
			quote = lex[i];
		else if (lex[i] == '~')
			lex = sh_exp_til_fnd(lex, &i);
		i++;
	}
	return (lex);
}
