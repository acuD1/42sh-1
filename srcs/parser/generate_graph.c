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
	set_string_token(tab);
	set_exp_token(tab);
	set_quote_token(tab);
	set_dbquote_token(tab);
	set_forward_token(tab);
	set_backward_token(tab);
	set_dgreat_token(tab);
	set_dless_token(tab);
	set_semicolon_token(tab);
	set_pipe_token(tab);
	set_ionumber_token(tab);
	set_assign_token(tab);
	return (start);
}