#include "shell.h"

void		sh_disp_part(t_line *line, t_tc tc, size_t i, int l)
{
	while (l--)
	{
		ft_putchar(line->str[i++]);
		if (line->str[i - 1] != '\n' && line->cur != i
				&& tc.coord[i - 1].x == tc.coord[line->used + 1].x - 1)
		{
			ft_putchar_fd(' ', 0);
			tputs(tc.le, 0, termput);
		}
		i += 1;
	}
}

int			sh_display(t_line *line, t_coord **coord, t_tc tc, char *save)
{
	int		syntax;

	syntax = (!save && ft_strequ(getenv("SYNTAX"), "on") ? 1 : 0);
	if (syntax)
		line->cur = sh_move_cur(line->cur, 0, *coord, tc);
	if (sh_clear(line, coord, tc) < 0)
		return (-1);
	if (syntax)
		sh_display_syntax(line, tc);
	else
		sh_disp_part(line, tc, line->cur, line->used + line->cur);
	line->cur = sh_move_cur(line->used, line->pos, *coord, tc);
	return (0);
}

/*
   int			sh_display(t_line *line, t_coord **coord, t_tc tc, char *save)
   {
   t_token	*lexer;
   char	*syntax;

   syntax = getenv("SYNTAX");
   lexer = NULL;
   if (!syntax || !ft_strequ(syntax, "ON") || save)
   {
   if (sh_clear(line, coord, tc) < 0)
   return (-1);
   ft_putstr_fd(line->str + line->cur, 0);
   }
   else
   {
   line->cur = sh_move_cur(line->cur, 0, *coord, tc);
   if (sh_clear(line, coord, tc) < 0)
   return (-1);
   sh_display_syntax(line->str);
   }
   sh_disp_nl(line, *coord, tc);
   line->cur = sh_move_cur(line->used, line->pos, *coord, tc);
   return (0);
   }
   */

/* OLD VERSION
   int		sh_display(t_line *line, t_coord **coord, t_tc tc, char *save)
   {
   size_t	i;

   (void)save;
   if (sh_clear(line, coord, tc) < 0)
   return (-1);
   i = line->cur;
   while (line->str[i])
   {
   ft_putchar_fd(line->str[i++], 0);
   if (line->str[i - 1] != '\n' && line->cur != i
   && (*coord)[i - 1].x == (*coord)[line->used + 1].x - 1)
   {
   ft_putchar_fd(' ', 0);
   tputs(tc.le, 0, termput);
   }
   }
   line->cur = sh_move_cur(i, line->pos, *coord, tc);
   return (0);
   }
   */
