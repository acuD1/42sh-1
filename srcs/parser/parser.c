#include "parser.h"

static int	node_is_ok(enum e_type to_find, t_graph *graph, enum e_type *type)
{
	int		i;

	i = 0;
	while (i < graph[*type].nb_of_good_type)
	{
		if (to_find == graph[*type].good_type[i])
		{
			*type = to_find;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

static int			parse_tokens(t_list **lst, t_graph *graph)
{
	t_token 	*token;
	enum e_type	state;

	state = START_TYPE;
	while (*lst)
	{
		token = (t_token *)(*lst)->data;
		if (!(node_is_ok(token->type, graph, &state)))
		{
			print_error_debug(token->type, 0);
			return (FALSE);
		}
		print_token_debug(token);
		if (token->type == E_END)
			return (TRUE);
		else
			print_arrow_debug(0);
		*lst = (*lst)->next;
	}
	return (FALSE);
}

void		parser(t_list *lst)
{
	static t_graph	*graph = NULL;

	ft_printf("\n------- | PARSER | -------\n\n");
	if (!graph && !(graph = generate_graph()))
		print_result_debug(1);
	else if (!lst || parse_tokens(&lst, graph))
		print_result_debug(0);
	else
		print_result_debug(1);
}
