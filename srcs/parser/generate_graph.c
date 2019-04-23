#include "parser.h"

static void		set_graph(t_graph *tab)
{
	set_start_token(tab);
	set_word_token(tab);
	set_redirect_token(tab);
	set_assign_token(tab);
	set_semicolon_token(tab);
	set_pipe_token(tab);
	set_ionumber_token(tab);
}

t_graph			*generate_graph(void)
{
	static t_graph		tab[NB_OF_TOKENS + 1];
	int					i;

	i = 0;
	while (i < NB_OF_TOKENS + 1)
	{
		ft_bzero(&tab[i], sizeof(t_graph));
		tab[i].type = i;
		i++;
	}
	set_graph(tab);
	return (tab);
}
