#include "parser.h"

static int			node_is_ok(t_token *token, t_graph **graph)
{
	t_graph		*tmp;
	t_graph		*node;
	t_list		*tmp_lst;

	tmp = *graph;
	tmp_lst = tmp->lst;
	while (tmp->lst)
	{
		node = *(t_graph **)tmp->lst->data;
		if (node->type == token->type)
		{
			*graph = node;
			print_token_debug(token);
			tmp->lst = tmp_lst;
			return (TRUE);
		}
		tmp->lst = tmp->lst->next;
	}
	tmp->lst = tmp_lst;
	return (FALSE);
}

static int			parse_tokens(t_list **lst, t_graph **graph)
{
	t_token *token;

	while (*lst)
	{
		token = (t_token *)(*lst)->data;
		if (!(node_is_ok(token, graph)))
		{
			print_error_debug(token->type, 0);
			return (FALSE);
		}
		else if (token->type == E_END)
			return (TRUE);
		else
			print_arrow_debug(0);
		*lst = (*lst)->next;
	}
	return (FALSE);
}

void		parser(t_list *lst)
{
	t_graph	*graph;
	t_graph	**tab;
	t_graph	*start;

	ft_printf("\n------- | PARSER | -------\n\n");
	start = NULL;
	tab = NULL;
	if (!(graph = generate_graph(start, tab)))
		print_result_debug(1);
	else if (!lst || parse_tokens(&lst, &graph))
		print_result_debug(0);
	else
		print_result_debug(1);
	free_graph(start, tab);
}
