#ifndef SHELL_H
# define SHELL_H

/*
**	EXTERN LIB
*/

# include <sys/ioctl.h>
# include <termios.h>
# include <termcap.h>

/*
**	DEFINE
*/

# define HIST_FILE ".21sh_history"
# define ERROR_MAX 5
# define EOL 4
# define LEXER 2
# define DISP 1

/*
**	RESSOURCES
*/

# include "../libft/includes/libft.h"
# include "sh_category.h"
# include "sh_struct.h"

/*
**	PROTO
*/

# include "sh_environment.h"
# include "sh_hci.h"
# include "sh_initialization.h"
# include "sh_parser.h"

////////////////
void displex(t_token *lexer);
void disphist(t_line *line);
void dispcoord(t_coord *c, t_line *l);
void disptree(t_tree *root);
////////////////

#endif
