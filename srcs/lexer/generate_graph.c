#include "parser.h"

t_graph		*generate_graph(void)
{
	t_graph	**tab;
	t_graph	*start;
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
	set_start_token(start, tab);
	set_string_token(start, tab);
	set_if_token(start, tab);
	set_else_token(start, tab);
	set_elif_token(start, tab);
	set_fi_token(start, tab);
	set_bracket_open_token(start, tab);
	set_bracket_close_token(start, tab);
	return (start);
}
