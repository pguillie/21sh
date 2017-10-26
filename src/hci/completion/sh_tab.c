#include "shell.h"

//
//ICI PROCHAINEMENT:
//	__ Function de Ludo __
//

static char	*sh_tab_split(char *lexeme, char *dir)
{
	size_t	i;

	if (dir)
		ft_bzero(dir, PATH_SIZE);
	i = 0;
	while (lexeme[i])
	{
		if (lexeme[i] == '/')
		{
			if (dir)
				ft_strncat(dir, lexeme, i + 1);
			lexeme += i + 1;
			i = 0;
		}
		else
			i += 1;
	}
	if (dir)
		!dir[0] ? dir[0] = '.' : 0;
	return (lexeme);
}

static void	sh_tab_space(char *word, char ret[], size_t i)
{
	char	last;
	size_t	j;

	j = 0;
	while (word[i])
	{
		last = word[i];
		ret[j++] = word[i++];
	}
	if (last != '/')
		ret[j++] = ' ';
	while (j < PATH_SIZE)
		ret[j++] = '\0';
}

static void	sh_tab_del(char *array[])
{
	size_t	i;

	i = 1;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i += 1;
	}
	free(array);
}

int			sh_tab(t_line *line, t_coord **coord, t_tc tc)
{
	char	**array;
	char	*lexeme;
	char	dir[PATH_SIZE];
	int		category;
	int		ret;

	lexeme = "";
	category = CMD;
	//FUNCTION_DE_LUDO(line->str, line->cur, &lexeme, &category);
	if (!(array = (char**)ft_memalloc(sizeof(char*) * 2)))
		return (0);
	array[0] = sh_tab_split(lexeme, dir);
	if (!(array = sh_tab_find(array, dir, category)))
		return (0);
	ret = 0;
	if (array[1] && !array[2])
	{
		sh_tab_space(array[1], dir, ft_strlen(array[0]));
		ret = sh_tab_comp(line, coord, tc, dir);
	}
	else if (array[1])
		ret = sh_tab_multi(line, coord, tc, array);
	sh_tab_del(array);
	return (ret);
}
