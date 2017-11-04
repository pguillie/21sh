// #include "shell.h"
//
//  // FONCTIONS DE DEBUGAGE //
//
// void	displex(t_token *lex)
// {
// 	ft_putendl("=== DISPLEX ===");
// 	while (lex)
// 	{
// 		ft_printf("category:%2d -- lexeme:%s\n", lex->category, lex->lexeme);
// 		lex = lex->next;
// 	}
// 	ft_putendl(" == end lex ==");
// }
//
// void	disphist(t_line *line)
// {
// 	ft_putendl("*** DISPHIST ***");
// 	while (line)
// 	{
// 		ft_printf("hist: '%s'\n", line->str);
// 		line = line->up;
// 	}
// 	ft_putendl(" ** end hist **");
// }
//
// void	dispcoord(t_coord *coord, t_line *line)
// {
// 	size_t	i;
//
// 	i = 0;
// 	while (i <= line->used + 1)
// 	{
// 		ft_printf("%zu: (%d;%d) `%c'\n", i, coord[i].x, coord[i].y, line->str[i]);
// 		i++;
// 	}
// }
//
// void	disparser(t_cmd ***p, int *op)
// {
// 	int i;
// 	int j;
// 	int	l;
//
// 	i = 0;
// 	ft_printf("$ $ $ DISPARSER $ $ $\n");
// 	if (p)
// 	{
// 		while (p[i])
// 		{
// 			j = 0;
// 			while (p[i][j])
// 			{
// 				l = 0;
// 				printf("NEW\n");
// 				while (p[i][j]->redir[l].type)
// 				{
// 					printf("\tREDIR: %d/%s/%s/%d\n",
// 							p[i][j]->redir[l].left,
// 							p[i][j]->redir[l].type,
// 							p[i][j]->redir[l].right,
// 							p[i][j]->redir[l].file);
// 					l++;
// 				}
// 				l = 0;
// 				while (p[i][j]->av[l])
// 				{
// 					printf("cmd: %s\n", p[i][j]->av[l]);
// 					l++;
// 				}
// 				j++;
// 			}
// 			p[i + 1] ? printf("--%d--\n", op[i]) : 0;
// 			i++;
// 		}
// 	}
// 	ft_printf("  $   ENDPARSER   $\n");
// }
//
// void	dispeof(char *fifo[32])
// {
// 	int	i;
//
// 	i = 0;
// 	ft_putendl("### beg eof ###");
// 	while (i < 32 && fifo[i])
// 		ft_putendl(fifo[i++]);
// 	ft_putendl(" ## end eof ##");
// }
