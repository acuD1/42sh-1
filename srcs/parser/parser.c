#include "parser.h"

static int	need_subprompt(enum e_type state, enum e_type type)
{
	if (state == E_PIPE && type == E_END)
		return (TRUE);
	return (FALSE);
}

static int	manage_error_and_subprompt(enum e_type state, enum e_type type,
										t_list *lst)
{
	if (need_subprompt(state, type))
	{
		/*
		** -----> call subprompt
		** -----> call lexer and get a new lst of tokens
		** -----> add_back new lst to current lst
		** -----> don't update state
		*/
		(void)lst;
		ft_dprintf(2, "21sh: \033[33mNEED TO CALL A SUB_PROMPT\033[0m\n");
		return (TRUE);
	}
	ft_dprintf(2, "21sh: syntax error near unexpected token `%c'\n",
				type < SINGLE_SIGNS ? ALLCHAR[type] : 'S');
	return (FALSE);
}

static int	node_is_ok(enum e_type to_find, enum e_type *type, t_graph *graph)
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

static int			parse_tokens(t_list *lst, t_graph *graph)
{
	t_token 	*token;
	enum e_type	state;

	state = START_TYPE;
	while (lst)
	{
		token = (t_token *)lst->data;
		if (!(node_is_ok(token->type, &state, graph)))
		{
			if (!manage_error_and_subprompt(state, token->type, lst))
				return (FALSE);
		}
		lst = lst->next;
	}
	return (TRUE);
}

int		parser(t_list *lst)
{
	static t_graph	*graph = NULL;

	if (!graph)
		graph = generate_graph();
	return (!lst || parse_tokens(lst, graph));
}

/*
*****************************************************************
************************* DEBUG PARSER **************************
*****************************************************************
**
**	static int			parse_tokens(t_list *lst, t_graph *graph)
**	{
**		t_token 	*token;
**		enum e_type	state;
**	
**		state = START_TYPE;
**		while (lst)
**		{
**			token = (t_token *)lst->data;
**			if (!(node_is_ok(token->type, &state, graph)))
**			{
**				print_error_debug(token->type, 0);
**				print_error_parser(token->type);
**				return (FALSE);
**			}
**			print_token_debug(token);
**			print_arrow_debug(0);
**			lst = lst->next;
**		}
**		return (TRUE);
**	}
**
**	int		parser(t_list *lst)
**	{
**		static t_graph	*graph = NULL;
**	
**		ft_printf("\n------- | PARSER | -------\n\n");
**		if (!graph && !(graph = generate_graph()))
**		{
**			print_result_debug(1);
**			return (FALSE);
**		}
**		else if (!lst || parse_tokens(lst, graph))
**			print_result_debug(0);
**		else
**		{
**			print_result_debug(1);
**			return (FALSE);
**		}
**		return (TRUE);
**	}
**
****************************************************************
****************************************************************
****************************************************************
*/
