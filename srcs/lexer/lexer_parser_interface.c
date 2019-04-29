/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_interface.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 22:31:09 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/29 15:54:00 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	init_process(t_process *process)
{
	ft_bzero(process, sizeof(t_process));
	process->fd.in = 0;
	process->fd.out = 1;
	process->fd.err = 2;
}

/*
int		lexer_parser(t_parser *parse, t_graph *graph, char *input)
{
	if (input == NULL || *input == '\0')
		return (FAILURE);
	if ((parse->token_list = lexer(input)) == NULL)
		return (FAILURE);
	///// DEBUG LEXER /////
	ft_lstiter(parse->token_list, print_token);
	ft_putchar('\n');
	///////////////////////
	if (parser(graph, parse->token_list) == FAILURE)
		return (FAILURE);
	get_token(parse);
	parser_state(parse);
	///// DEBUG PARSER2 ///
	ft_putchar('\n');
	return (parse->job_list == NULL ? FAILURE : SUCCESS);
	//return (parse->token_list && parse->job_list ? FAILURE : SUCCESS);
}
*/
