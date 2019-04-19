#include "parser.h"

static void		set_graph(t_graph **tab, t_graph *start)
{
	set_start_token(start, tab);
	set_word_token(tab);
	set_redirect_token(tab);
	set_assign_token(tab);
	set_semicolon_token(tab);
	set_pipe_token(tab);
	set_ionumber_token(tab);
}

t_graph			*generate_graph(t_graph *start, t_graph **tab)
{
	int		i;

	if (!(tab = (t_graph **)malloc(sizeof(t_graph *) * NB_OF_TOKENS)))
		return (NULL);
	i = 0;
	while (i < NB_OF_TOKENS)
	{
		if (!(tab[i] = (t_graph *)malloc(sizeof(t_graph))))
			return (NULL);
		ft_bzero(tab[i], sizeof(t_graph));
		tab[i]->type = i;
		i++;
	}
	if (!(start = (t_graph *)malloc(sizeof(t_graph))))
		return (NULL);
	ft_bzero(start, sizeof(t_graph));
	set_graph(tab, start);
	return (start);
}

void			free_graph(t_graph *start, t_graph **tab)
{
	int		i;

	i = 0;
	if (tab)
	{
		while (i < NB_OF_TOKENS)
		{
			free(tab[i]);
			tab[i++] = NULL;
		}
		free(tab);
		tab = NULL;
	}
	if (start)
	{
		free(start);
		start = NULL;
	}
}
