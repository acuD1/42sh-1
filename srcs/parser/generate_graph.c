#include "parser.h"

t_graph		*generate_graph(void)
{
	t_graph	**graph;
	t_graph	*start;
	int		i;

	if (!(graph = (t_graph **)malloc(sizeof(t_graph *) * NB_OF_TOKENS)))
		return (NULL);
	i = 0;
	while (i < NB_OF_TOKENS)
	{
		if (!(graph[i] = (t_graph *)malloc(sizeof(t_graph))))
			return (NULL);
		ft_bzero(graph[i], sizeof(t_graph));
		graph[i]->type = i;
		i++;
	}
	if (!(start = (t_graph *)malloc(sizeof(t_graph))))
		return (NULL);
	ft_bzero(start, sizeof(t_graph));
	set_start_token(start, graph);
	set_string_token(graph);
	set_exp_token(graph);
	set_quote_token(graph);
	set_dbquote_token(graph);
	set_forward_token(graph);
	set_backward_token(graph);
	set_dgreat_token(graph);
	set_dless_token(graph);
	set_semicolon_token(graph);
	set_pipe_token(graph);
	set_ionumber_token(graph);
	set_assign_token(graph);
	return (start);
}
