/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:41:49 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/01 01:04:05 by cempassi         ###   ########.fr       */
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

static void	print_parser_error(enum e_type type)
{
	static const char *signs[] = {"&&", "OR", ";;", "<<", ">>", "<&", ">&"
		, "<>", "<<-", ">|", "==", "!="};
	static const char *script[] = {CASE, DO, DONE, ELIF, ELSE, ESAC, FI, FOR
									, IF, IN, THEN, UNTIL, WHILE};

	ft_dprintf(2, "21sh: syntax error near unexpected token ");
	if (type == E_STRING)
		ft_dprintf(2, "`STRING'\n");
	else if (type == E_SPSTRING)
		ft_dprintf(2, "`SPSTRING'\n");
	else if (type < SINGLE_SIGNS)
		ft_dprintf(2, "`%c'\n", ALLCHAR[type]);
	else if (type >= SINGLE_SIGNS && type < SIGNS)
		ft_dprintf(2, "`%s'\n", signs[type - SINGLE_SIGNS]);
	else if (type >= SIGNS && type < SIGNS + 13)
		ft_dprintf(2, "`%s'\n", script[type - SIGNS]);
	else if (type == E_IO_NUMBER)
		ft_dprintf(2, "`IO_number'\n");
	else if (type == E_ASSIGN)
		ft_dprintf(2, "`assign (=)'\n");
	else
		ft_dprintf(2, "`end'\n");
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
			new_token = lexer(line);
			ft_strdel(&line);
		}
		ft_putchar('\n');
		free((*lst)->next);
		(*lst)->next = new_token;
		return (TRUE);
	}
	print_parser_error(type);
	return (FALSE);
}

static int	node_is_ok(enum e_type to_find, enum e_type *type,
				char *data, t_graph *graph)
{
	int		i;

	i = 0;
	if ((*(type) == E_GREATAND || *(type) == E_LESSAND
				|| *(type) == E_DGREATAND)
			&& data == NULL)
		return (FALSE);
	while (graph[*type].good_type[i] != E_ERROR)
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

int			parser(t_graph *graph, t_list *lst)
{
	t_token 	*token;
	enum e_type	state;
	char		*data;
	t_list		*tmp;

	state = E_DEFAULT;
	tmp = lst;
	if (lst)
		data = ((t_token *)lst->data)->data;
	while (lst != NULL)
	{
		token = (t_token *)lst->data;
		if ((node_is_ok(token->type, &state, data, graph)) == FALSE)
		{
			if (manage_error_and_subprompt(state, token->type, &tmp) == FALSE)
				return (FAILURE);
			lst = tmp;
		}
		else
			tmp = lst;
		data = token->data;
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
