#include "shell.h"

static int		sh_get_highest(t_token *lexer)
{
	t_token	*b;
	int		high;

	high = 0;
	b = lexer;
	while (b)
	{
		if (b->category > high)
			high = b->category;
		b = b->next;
	}
	return (high);
}

static int		sh_split(char **op, t_token *lexer,
				t_token **left, t_token **right)
{
	int		high;

	if (!(high = sh_get_highest(lexer)))
		return (0);
	*right = lexer;
	while (*right && (*right)->category != high)
	{
		*left = *right;
		*right = (*right)->next;
	}
	if (!(*op = ft_strdup((*right)->lexeme)))
		return (-1);
	*right = (*right)->next;
	if (*left)
	{
		ft_strdel(&((*left)->next->lexeme));
		ft_memdel((void**)&((*left)->next));
		*left = lexer;
	}
	return (1);
}

static t_token	*sh_join_token(t_token *l, t_token *r)
{
	t_token *f;

	if (l)
	{
		f = l;
		while (f->next)
			f = f->next;
		f->next = r;
		return (l);
	}
	return (r);
}

int				sh_parser(t_token *lexer, t_tree **root)
{
	t_token	*left;
	t_token	*right;

	left = NULL;
	right = NULL;
	if (!lexer)
	{
		*root = NULL;
		return (0);
	}
	if (!(*root = (t_tree*)ft_memalloc(sizeof(t_tree))))
		return (-1);
	(*root)->cmd = NULL;
	(*root)->op = NULL;
	if (sh_split(&((*root)->op), lexer, &left, &right) < 0)
		return (sh_tree_del(root));
	if (!(*root)->op && !((*root)->cmd = sh_cmd_new(lexer)))
		return (sh_tree_del(root));
	if (sh_parser(left, &((*root)->left)) < 0
			|| sh_parser(right, &((*root)->right)) < 0)
		return (sh_tree_del(root));
	lexer = sh_join_token(left, right);
	return (0);
}
