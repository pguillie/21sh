#ifndef SHELL_H
# define SHELL_H

# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include "../libft/includes/libft.h"
# include "key.h"

# define HIST_FILE ".21sh_history"

typedef struct	s_tc
{
	int		on;
	int		prompt;
	char	data[2048];
	char	buff[2048];
	char	*ce;
	char	*dc;
	char	*dn;
	char	*le;
	char	*nd;
	char	*up;
}				t_tc;

typedef struct	s_line
{
	char			*str;
	size_t			cur;
	size_t			used;
	size_t			capacity;
	struct s_line	*prev;
	struct s_line	*next;
}				t_line;

typedef struct	s_coord
{
	int	x;
	int	y;
}				t_coord;

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
**	Human-Computer Interaction
*/

t_token	*sh_hci(t_tc termcaps);
char	*sh_cooked_edition(void);
char	*sh_raw_edition(t_line *hist, t_tc termcaps);

/*
**	HCI	CUR_MOTION
*/

int		sh_cur_motion(long input, t_line *line, size_t *pos);
size_t	sh_move_cur(size_t origin, size_t dest, t_coord *coord, t_tc tc);
t_coord	*sh_create_coord(t_line *line, int prompt);

/*
**	HCI	EDITION
*/

char	*sh_raw_edit(t_line *line, char *last, t_tc termcaps);
char	*sh_cooked_edit(void);
int		sh_line_edit(t_line *line, t_tc termcaps);
t_line	*sh_line_hist(t_line *line, t_line *new, t_coord *coord, t_tc tc);
int		sh_ins_char(t_line *line, t_tc tc, t_coord *coord, char c);
void	sh_del_char(t_line *line, t_tc tc, t_coord *coord, long input);
int		sh_prompt(int mode);
int		termput(int c);

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
