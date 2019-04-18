/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 15:44:20 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/19 01:17:02 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_token(t_parser *parse)
{
	t_list		*node;

	node = parse->token_list;
	parse->token_list = parse->token_list->next;
	ft_memcpy(&parse->token, node->data, sizeof(t_token));
	ft_lstdelone(&node, NULL);
}

void	init_parser(t_parser *parse)
{
	parse->state = P_START;
	init_parsing(parse);
	get_token(parse);
}

void	init_command(t_exec *command)
{
	ft_bzero(command, sizeof(t_exec));
	command->fdin = 0;
	command->fdout = 1;
	command->fderror = 2;
}

t_list	*parser_state(t_list *token_list)
{
	t_parser	parse;

	ft_bzero(&parse, sizeof(t_parser));
	parse.token_list = token_list;
	init_parser(&parse);
	ft_stckinit(&parse.stack);
	init_command(&parse.command);
	while (parse.state != P_END && parse.state != P_ERROR)
	{
		if (parse.state == P_STOP)
			break;
		ft_printf("parser state : [%d] | next token : [%d]\n"
				, parse.state, parse.token.type);
		parse.parsing[parse.state][parse.token.type](&parse);
	}
	ft_printf("END ->>> parser state : [%d] | next token : [%d]\n"
			, parse.state, parse.token.type);
	return (parse.parse_output);
}
