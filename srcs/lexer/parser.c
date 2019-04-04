#include "parser.h"

int			node_is_ok(t_token *token, t_graph **graph)
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
			print_token_debug(node->type);
			tmp->lst = tmp_lst;
			return (TRUE);
		}
		tmp->lst = tmp->lst->next;
	}
	tmp->lst = tmp_lst;
	return (FALSE);
}

int			parse_tokens(t_list **lst, t_graph **graph, enum e_type ref)
{
	t_token *token;

	while (*lst)
	{
		token = (t_token *)(*lst)->data;
		if (token->type != E_SPACE)
		{
			if (!(node_is_ok(token, graph)))
			{
				print_error_debug(token->type, 0);
				return (FALSE);
			}
			if (ref == token->type)
				return (TRUE);
			if ((*graph)->event == RECALL)
			{
				print_arrow_debug(1);
				*lst = (*lst)->next;
				if (!(parse_tokens(lst, graph, (*graph)->type_end)))
					return (FALSE);
				print_arrow_debug(2);
			}
			else if ((*graph)->event == BACK)
			{
				token = (t_token *)(*lst)->data;
				*lst = (*lst)->next;
				return (ref == token->type || ref == NB_OF_TOKENS + 1);
			}
			else
				print_arrow_debug(0);
		}
		*lst = (*lst)->next;
	}
	if (ref != NB_OF_TOKENS + 1)
	{
		print_error_debug(ref, 1);
		return (FALSE);
	}
	return (TRUE);
}

void		parser(t_list *lst)
{
	t_graph	*graph;

	ft_printf("------- | PARSER | -------\n\n");
	graph = generate_graph();
	if (parse_tokens(&lst, &graph, NB_OF_TOKENS + 1))
		print_result_debug(0);
	else
		print_result_debug(1);
}
