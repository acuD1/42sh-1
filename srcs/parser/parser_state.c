/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:44:20 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/29 13:20:53 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
	while (parse->state != P_END && parse->state != P_ERROR)
	{
		if (parse->state == P_STOP)
			break;
		parse->last_state = parse->state;
		ft_printf("parser state : [%d] | next token : [%d]\n"
				, parse->state, parse->token.type);
		parsing[parse->state][parse->token.type](parse);
	}
	ft_printf("END ->>> parser state : [%d] | next token : [%d]\n"
			, parse->state, parse->token.type);
	return (parse->job_list);
}
