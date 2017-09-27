#ifndef SHELL_H
# define SHELL_H

/*
**	EXTERN LIB
*/

# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <signal.h>
# include <pwd.h>
# include <dirent.h>
# include <termcap.h>
# include <time.h>

/*
**	DEFINE
*/

# define SHELL "21sh"
# define VERSION "1.0"
# define PATCH "0"

# define HIST_FILE ".21sh_history"
# define ERROR_MAX 5
# define PRT_SIZE 256
# define PROMPT_DIRTRIM 3
# define PS1 "\\s-\\v\\$ "
# define PS2 "> "
# define PS3 "#? "
# define PS4 "+ "


# define EOL 4
# define LEXER 2
# define DISP 1

# define CASE(x) (x | 32)

/*
**	RESSOURCES
*/

# include "../libft/includes/libft.h"
# include "sh_key.h" // on garde?
# include "sh_category.h"
# include "sh_struct.h"

/*
**	PROTO
*/

# include "sh_environment.h"
# include "sh_hci.h"
# include "sh_initialization.h"

////////////////
void displex(t_token *lexer);
void disphist(t_line *line);
void dispcoord(t_coord *c, t_line *l);
////////////////

#endif
