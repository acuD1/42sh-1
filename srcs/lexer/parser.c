#include "lexer.h"

#define NB_OF_TOKENS 39
#define TRUE 1
#define FALSE 0

enum	e_event
{
	NO_EVENT,
	START_GRAPH,
	END_GRAPH,
	RECALL
};

typedef struct s_graph	t_graph;

struct s_graph
{
	enum	e_event	event;
	enum	e_type	type;
	enum	e_type	type_end;
	t_list 			*lst;
};

void		set_start_token(t_graph *start, t_graph **tab)
{
	ft_lstadd(&start->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
}

void		set_string_token(t_graph *start, t_graph **tab)
{
	(void)start;
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_PARENT_OPEN], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_PARENT_CLOSE], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_IF], sizeof(t_graph **)));
	ft_lstadd(&tab[E_STRING]->lst, ft_lstnew(&tab[E_FI], sizeof(t_graph **)));
}

void		set_if_token(t_graph *start, t_graph **tab)
{
	(void)start;
	tab[E_IF]->event = RECALL;
	tab[E_IF]->type_end = E_FI;
	ft_lstadd(&tab[E_IF]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
	ft_lstadd(&tab[E_IF]->lst, ft_lstnew(&tab[E_FI], sizeof(t_graph **)));
}

void		set_fi_token(t_graph *start, t_graph **tab)
{
	(void)start;
	ft_lstadd(&tab[E_FI]->lst, ft_lstnew(&tab[E_STRING], sizeof(t_graph **)));
}

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
	return (start);	
}

int			node_is_ok(t_token *token, t_graph **graph)
{
	t_graph		*tmp;
	t_graph		*node;

	tmp = *graph;
	while (tmp && tmp->lst)
	{
		node = *(t_graph **)tmp->lst->data;
		if (node->type == token->type)
		{
			*graph = node;
			ft_printf("\033[37m         ------\n         | %2d |\n         ------\n", node->type);
			return (TRUE);
		}
		tmp->lst = tmp->lst->next;
	}
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
			ft_printf("\033[37m         ------\n         | %2d |\n         ------\n", token->type);
			return (TRUE);
		}
		if (token->type != E_SPACE)
		{
			if (!(node_is_ok(token, &graph)))
				return (FALSE);
			if (graph->event == RECALL)
			{
				ft_printf("\033[36m           ||\n           up\n           ||\n           vv\n\033[0m");
				*lst = (*lst)->next;
				if (!(parse_tokens(lst, graph, graph->type_end)))
					return (FALSE);
				ft_printf("\033[36m           ||\n          down\n           ||\n           vv\n\033[0m");
				*lst = (*lst)->next;
			}
			else
				ft_printf("\033[33m           ||\n           vv\n\033[0m");
		}
		if (*lst)
			*lst = (*lst)->next;
	}
	return (ref == NB_OF_TOKENS + 1);
}

void		parser(t_list *lst)
{
	t_graph	*graph;

	ft_printf("------ | PARSER | ------\n\n");
	graph = generate_graph();
	if (parse_tokens(&lst, graph, NB_OF_TOKENS + 1))
		ft_printf("\033[32m         ------\n         | OK |\n         ------\n\n\033[0m");
	else
		ft_printf("\033[31m         ------\n         | KO |\n         ------\n\n\033[0m");
}
