#include "shell.h"

static int	sh_convert_move(char *esc)
{
	if (esc[1] == '[' && ((esc[2] >= 'A' && esc[2] <= 'D')
				|| esc[2] == 'F' || esc[2] == 'H'))
		return (1 << ((esc[2] ^ 64) - 1));
	if (esc[1] == '[' && esc[2] == '1' && esc[3] == ';' && esc[4] == '5'
			&& (esc[5] >= 'A' && esc[5] <= 'D'))
		return ((1 << ((esc[5] ^ 64) - 1)) | CTL);
	return (0);
}

static int	sh_check_move(t_line *line, t_coord *coord, char id)
{
	line->h_smd = 0;
	if (id & UP)
		return ((id & CTL || coord[line->cur].y != coord[0].y)
				&& sh_move_line_u(line, coord));
	else if (id & DOWN)
		return ((id & CTL || coord[line->cur].y != coord[line->used].y)
				&& sh_move_line_d(line, coord));
	else if (id & RIGHT && line->str[line->cur])
		line->pos = id & CTL ? sh_move_word_r(line) : line->cur + 1;
	else if (id & LEFT && line->cur)
		line->pos = id & CTL ? sh_move_word_l(line) : line->cur - 1;
	else if (id & HOME)
		line->pos = 0;
	else if (id & END)
		line->pos = line->used;
	else
		return (0);
	return (1);
}

int			sh_move_able(char *esc, t_line *line, t_coord *coord,
		int *hist_search)
{
	char	id;

	id = sh_convert_move(esc);
	if (line->h_smd == 1 && (id & UP || id & DOWN))
		*hist_search = 1;
	else
		return (sh_check_move(line, coord, id));
	return (0);
}
