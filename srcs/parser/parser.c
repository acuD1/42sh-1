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
			print_token_debug(token);
			tmp->lst = tmp_lst;
			return (TRUE);
		}
		tmp->lst = tmp->lst->next;
	}
	tmp->lst = tmp_lst;
	return (FALSE);
}

int			ref_end_is_ok(t_list *lst_ref, enum e_type token_ref)
{
	enum e_type ref;
	t_list		*tmp;


	tmp = lst_ref;
	while (lst_ref)
	{
		ref = *(enum e_type *)(lst_ref->data);
		if (token_ref == ref)
		{
			lst_ref = tmp;
			return (TRUE);
		}
		lst_ref = lst_ref->next;
	}
	lst_ref = tmp;
	return (FALSE);
}

int			parse_tokens(t_list **lst, t_graph **graph, t_list *ref, enum e_type start)
{
	t_token *token;

	while (*lst)
	{
		token = (t_token *)(*lst)->data;
		if (!(node_is_ok(token, graph)))
		{
			print_error_debug(token->type, 0);
			(*graph)->event = ERROR_GRAPH;
			return (FALSE);
		}
		if (ref_end_is_ok(ref, token->type))
			return (TRUE);
		if ((*graph)->event == START_GRAPH && start != NB_OF_TOKENS + 1)
		{
			print_error_debug(0, 2);
			return (FALSE);
		}
		else if ((*graph)->event == BACK)
		{
			token = (t_token *)(*lst)->data;
			*lst = (*lst)->next;
			if (!ref)
				print_error_debug(0, 2);
			return (ref_end_is_ok(ref, token->type));
		}
		else if ((*graph)->event == RECALL)
		{
			if ((*graph)->type_parent && !ref_end_is_ok((*graph)->type_parent, start))
			{
				print_error_debug(0, 2);
				return (FALSE);
			}
			while ((*graph)->event == RECALL)
			{
				print_arrow_debug(1);
				*lst = (*lst)->next;
				if (!(parse_tokens(lst, graph, (*graph)->type_end, (*graph)->type)))
				{
					if ((*graph)->event != ERROR_GRAPH)
						print_error_debug(0, 2);
					return (FALSE);
				}
				print_arrow_debug(2);
			}
		}
		else
			print_arrow_debug(0);
		*lst = (*lst)->next;
	}
	if (ref)
	{
		print_error_debug(*(enum e_type *)(ref->data), 1);
		(*graph)->event = ERROR_GRAPH;
		return (FALSE);
	}
	if ((*graph)->end)
		return (TRUE);
	ft_printf("\033[31m ==> ERROR: bad last token (type %d)\033[0m\n", (*graph)->type);
	return (FALSE);
}

void		parser(t_list *lst)
{
	t_graph	*graph;

	ft_printf("------- | PARSER | -------\n\n");
	graph = generate_graph();
	if (parse_tokens(&lst, &graph, NULL, NB_OF_TOKENS + 1))
		print_result_debug(0);
	else
		print_result_debug(1);
}
