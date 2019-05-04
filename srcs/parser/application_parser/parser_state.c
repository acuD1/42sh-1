/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:44:20 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/04 18:22:32 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

char	*pop_token_data(t_stack *stack)
{
	t_token *token;
	char	*data;

	token = ft_stckpop(stack);
	data = token->data;
	free(token);
	return (data);
}

t_type	pop_token_type(t_stack *stack)
{
	t_token		*token;
	t_type		type;

	token = ft_stckpop(stack);
	type = token->type;
	free(token);
	return (type);
}

void	generate_filedesc(t_parser *parse, int first, int second, int action)
{
	t_list		*node;
	t_filedesc	fd;

	fd.action = action;
	fd.first = first;
	fd.second = second;
	node = ft_lstnew(&fd, sizeof(t_filedesc));
	ft_lstaddback(&parse->process.fd, node);
}

void	get_token(t_parser *parse)
{
	t_list		*node;

	if (parse->token_list == NULL)
		return ;
	node = parse->token_list;
	parse->token_list = parse->token_list->next;
	ft_memcpy(&parse->token, node->data, sizeof(t_token));
	ft_lstdelone(&node, NULL);
}

t_list	*parser_state(t_pstate parsing, t_parser *parse)
{
	get_token(parse);
	while (parse->state != P_END && parse->state != P_ERROR)
	{
		if (parse->state == P_STOP)
			break;
		parsing[parse->state][parse->token.type](parse);
	}
	return (parse->job_list);
}
