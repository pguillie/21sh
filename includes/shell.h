#ifndef SHELL_H
# define SHELL_H

# include <termios.h>
# include <termcap.h>
# include "../libft/includes/libft.h"

# define HIST_FILE ".21sh_history"

typedef struct	termios t_termios;

typedef struct	s_tc
{
	int		on;
	char	data[2048];
	char	buff[2048];
	char	*nd;
	char	*le;
}				t_tc;

typedef struct	s_line
{
	char			*str;
//	int				*pos[2]; //contient les coordonees (x;y) de chaque char de str -- (0;0) est le debut du prompt
	size_t			cur;
	size_t			used; // = ft_strlen(str) -> utile ? 
	size_t			capacity;
	struct s_line	*prev;
	struct s_line	*next;
}				t_line;

typedef struct	s_cpypst
{
	int		select[2];
	char	*clipboard;
}				t_cpypst;

typedef struct	s_token
{
	char			*lexeme;
	int				category;
	struct s_token	*next;
}				t_token;

/*
**	ENVIRONMENT
*/

char	**sh_envdup(char *env[]);
char	**sh_envvarsplit(char *name, char *env[]);
char	*sh_getenv(char *name, char *env[]);

/*
**	Human-Computer Interface
*/

t_token	*sh_hci(t_tc termcaps);
char	*sh_cooked_edition(void);
char	*sh_raw_edition(t_line *hist, t_tc termcaps);

/*
**	HCI	EDITION
*/

char	*sh_raw_edit(t_line *line, char *last, t_tc termcaps);
char	*sh_cooked_edit(void);

/*
**	HCI	HISTORY
*/

t_line	*sh_hist_read(void);
t_line	*sh_hline_new(char *str, t_line *prev);
int		sh_hist_write(char *line, char *last);
void	sh_hist_del(t_line **hist);

/*
**	INITIALIZATION
*/

int		sh_init(t_tc *init);
int		sh_init_env(void);
int		sh_init_termcaps(t_tc *init);

#endif
