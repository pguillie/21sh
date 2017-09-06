#ifndef SH_HCI_H
# define SH_HCI_H

/*
**	HUMAN-COMPUTER INTERACTION
*/

t_token	*sh_hci(t_tc *termcaps);
int		sh_edit(t_line *line, char *last, t_token **lexer, t_tc *termcaps);

/*
**	X-ABLE
*/

int		sh_move_able(char *esc, t_line *line, t_coord *coord);

/*
**	CONVERTIONS
*/

char	sh_conv(char *str);
char	sh_conv_oct(char *str);
char	sh_conv_hex(char *str);

/*
**	CUR_MOTION
*/

# define CTL 64
# define UP 1
# define DOWN 2
# define RIGHT 4
# define LEFT 8
# define END 32
# define HOME 128

int		sh_cur_motion(long input, t_line *line, size_t *pos, t_coord *coord);
size_t	sh_move_cur(size_t origin, size_t dest, t_coord *coord, t_tc tc);
size_t	sh_move_line(long input, t_coord *coord, t_line *line, int *ret);
size_t	sh_move_word(int move, t_line *line);
t_coord	*sh_create_coord(t_line *line, size_t prompt);

/*
**	EDITION
*/

int		sh_edit_line(t_line **line, char **save, t_token **lexer, t_tc *tc);
int		sh_esc(t_line **line, t_coord **coord, t_tc *tc);
int		sh_putesc(t_line **line, t_coord **coord, t_tc *tc);
void	sh_clear(t_line *line, t_coord *coord, t_tc tc);
void	sh_display(t_line *line, t_coord *coord, t_tc tc);
int		sh_del_l(t_line *line, t_coord **coord, t_tc tc);
int		sh_ins(t_line *line, t_coord **coord, t_tc tc, char c);
int		termput(int c);

/*
**	HISTORY
*/

t_line	*sh_hist_read(void);
t_line	*sh_hline_new(char *str, t_line *prev);
int		sh_hist_write(char *line, char *last);
void	sh_hist_del(t_line **hist);

/*
**	LEXER
*/

t_token	*sh_token_new(char *lexeme, size_t *i, int *status);
int		sh_lexer(char *str, t_token **begin);
int		sh_lex_word(char *str);
int		sh_metachar(char c);
int		sh_ctrl_op(char *str);
int		sh_rdir_op(char *str);
int		sh_token_del(t_token **begin);
int		sh_category(char *str, size_t *i, int *status);

/*
**	PROMPT
*/

int		sh_prompt(int mode);
int		sh_print_prompt(char *ps);
int		sh_prompt_conv(char c);
int		sh_prt_date(void);
int		sh_prt_host(char c);
int		sh_prt_time(char c);
int		sh_prt_user(void);
int		sh_prt_wdir(char c);
int		sh_prt_end(void);

#endif
