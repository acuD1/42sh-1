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
	set_fi_token(start, tab);
	set_bracket_open_token(start, tab);
	set_bracket_close_token(start, tab);
	return (start);
}


int			node_is_ok(t_token *token, t_graph **graph)
{
	t_graph		*tmp;
	t_graph		*node;
	t_list		*tmp_lst;

	tmp = *graph;
	tmp_lst = tmp->lst;
	while (tmp && tmp->lst)
	{
		node = *(t_graph **)tmp->lst->data;
		if (node->type == token->type)
		{
			*graph = node;
			print_token(node->type);
			tmp->lst = tmp_lst;
			return (TRUE);
		}
		tmp->lst = tmp->lst->next;
	}
	tmp->lst = tmp_lst;
	return (FALSE);
}

int			parse_tokens(t_list **lst, t_graph *graph, enum e_type ref)
{
	t_token *token;

	while (*lst && graph->lst)
	{
		token = (t_token *)(*lst)->data;
		if (ref == token->type)
		{
			print_token(token->type);
			return (TRUE);
		}
		else if (token->type == E_SPACE)
			*lst = (*lst)->next;
		else
		{
			if (!(node_is_ok(token, &graph)))
			{
				ft_printf("\033[31m ==> ERROR: token type %d is not possible\n\033[0m", token->type);
				return (FALSE);
			}
			if (graph->event == RECALL)
			{
				ft_printf("\033[34m            ||\n            up\n            ||\n            vv\n\033[0m");
				*lst = (*lst)->next;
				if (!(parse_tokens(lst, graph, graph->type_end)))
					return (FALSE);
				ft_printf("\033[36m            ||\n           down\n            ||\n            vv\n\033[0m");
			}
			else
			{
				ft_printf("\033[33m            ||\n            vv\n\033[0m");
			}
			*lst = (*lst)->next;
		}
	}
	if (ref != NB_OF_TOKENS + 1)
	{
		ft_printf("\033[31m ==> ERROR: miss token type %d\n\033[0m", ref);
		return (FALSE);
	}
	return (TRUE);
}

void		parser(t_list *lst)
{
	t_graph	*graph;

	ft_printf("------- | PARSER | -------\n\n");
	graph = generate_graph();
	if (parse_tokens(&lst, graph, NB_OF_TOKENS + 1))
		ft_printf("\033[32m         --------\n         |  OK  |\n         --------\n\n\033[0m");
	else
		ft_printf("\033[31m         --------\n         |  KO  |\n         --------\n\n\033[0m");
}
