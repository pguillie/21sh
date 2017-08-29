#ifndef SHELL_H
# define SHELL_H

# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>
# include "../libft/includes/libft.h"
# include "key.h"
# include "category.h"

# define HIST_FILE ".21sh_history"

typedef struct	s_tc
{
	int		on;
	int		prompt;
	int		select[2];
	char	*clipboard;
	char	data[2048];
	char	buff[2048];
	char	*cd;
	char	*ce;
	char	*dn;
	char	*le;
	char	*nd;
	char	*up;
	char	*vi;
	char	*ve;
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
**	HCI	(Human-Computer Interaction)
*/

t_token	*sh_hci(t_tc termcaps);
int		sh_ckd_edit(t_token **begin);
char	*sh_raw_edition(t_line *hist, t_tc termcaps);

/*
**	HCI	CONVERTIONS
*/

char	sh_conv(char *str);
char	sh_conv_oct(char *str);
char	sh_conv_hex(char *str);

/*
**	HCI	CUR_MOTION
*/

int		sh_cur_motion(long input, t_line *line, size_t *pos, t_coord *coord);
size_t	sh_move_cur(size_t origin, size_t dest, t_coord *coord, t_tc tc);
size_t	sh_move_line(long input, t_coord *coord, t_line *line, int *ret);
size_t	sh_move_word(long input, t_line *line);
t_coord	*sh_create_coord(t_line *line, size_t prompt);

/*
**	HCI	EDITION
*/

char	*sh_raw_edit(t_line *line, char *last, t_tc termcaps);
void	sh_disp_line(t_line *line, t_coord *coord, t_tc termcaps);
int		sh_line_edit(t_line **line, t_tc termcaps);
t_line	*sh_line_hist(t_line *line, t_line *new, t_coord **coord, t_tc tc);
int		sh_ins_char(t_line *line, t_tc tc, t_coord **coord, char c);
void	sh_del_char(t_line *line, t_tc tc, t_coord **coord, long input);
void	sh_del_after(t_line *line, t_tc tc, t_coord *coord);
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
**	HCI	LEXER
*/

int		sh_lexer(char *str, t_token **begin);
int		sh_lex_word(char *str);
int		sh_metachar(char c);
int		sh_ctrl_op(char *str);
int		sh_rdir_op(char *str);
t_token	*sh_token_del(t_token **begin);
t_token	*sh_token_new(char *lexeme, int *status);
int		sh_category(char *str, int *status);

/*
**	HCI	PROMPT
*/

int		sh_prompt(int mode);
int		sh_print_prompt(char *ps);
int		sh_prompt_conv(char *str);
int		sh_prompt_dollar(void);
int		sh_prompt_host(void);
int		sh_prompt_user(void);
int		sh_prompt_workdir(void);

/*
**	INITIALIZATION
*/

int		sh_init(t_tc *init);
int		sh_init_env(void);
int		sh_init_termcaps(t_tc *init);

#endif
