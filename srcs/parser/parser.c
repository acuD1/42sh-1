/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:41:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/02 03:22:01 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "interface_functions.h"

t_registry	*g_shell;

static int	need_subprompt(enum e_type state, enum e_type type)
{
	if (state == E_PIPE && type == E_END && g_shell->is_interactive == TRUE)
		return (TRUE);
	return (FALSE);
}

static int	manage_error_and_subprompt(enum e_type state, enum e_type type,
										t_list **lst)
{
	t_list		*new_token;
	char		*line;

	if (need_subprompt(state, type) == TRUE)
	{
		line = NULL;
		new_token = NULL;
		while (new_token == NULL)
		{
			invoke_sub_prompt(g_shell, &line, "pipe> ");
			g_shell->interface.state = INT_PS1;
			new_token = lexer(&g_shell->lexinfo, line);
			ft_strdel(&line);
		}
		ft_putchar('\n');
		free((*lst)->next);
		(*lst)->next = new_token;
		return (TRUE);
	}
	ft_dprintf(2, "21sh: syntax error near unexpected token `%s'\n",
						g_shell->grammar[type]);
	return (FALSE);
}

static int8_t	state_is_ok(enum e_type to_find, enum e_type *current,
							enum e_type possible_state[])
{
	uint8_t		i;

	i = 0;
	if (possible_state == NULL)
		return (FALSE);
	while (possible_state[i] != E_ERROR)
	{
		if (to_find == possible_state[i])
		{
			*current = to_find;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int8_t			parser(t_graph *graph, t_list *lst)
{
	t_token 	*token;
	t_list		*tmp;
	enum e_type	state;

	state = E_START;
	tmp = lst;
	while (lst != NULL)
	{
		token = (t_token *)lst->data;
		if ((state_is_ok(token->type, &state, graph[state].good_type)) == FALSE)
		{
			if (manage_error_and_subprompt(state, token->type, &tmp) == FALSE)
				return (FAILURE);
			lst = tmp;
		}
		else
			tmp = lst;
		lst = lst->next;
	}
	return (SUCCESS);
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
