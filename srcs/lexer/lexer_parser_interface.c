/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_interface.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 22:31:09 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/23 19:45:51 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	bzero_parsing(t_parser *parse)
{
	int		index;
	int		state;

	index = 0;
	while (index < PARSE_STATES)
	{
		state = 0;
		while (state < NB_OF_TOKENS)
			parse->parsing[index][state++] = error_parser;
		++index;
	}
}

void	init_process(t_process *process)
{
	ft_bzero(process, sizeof(t_process));
	process->fd.in = 0;
	process->fd.out = 1;
	process->fd.err = 2;
}

void	init_parser(t_parser *parse)
{
	ft_bzero(parse, sizeof(t_parser));
	parse->state = P_START;
	bzero_parsing(parse);
	init_parsing(parse);
	ft_stckinit(&parse->stack);
	init_process(&parse->process);
}

int		lexer_parser(t_parser *parse, char *input)
{
	if (!*input)
		return (0);
	if (!parse->token_list)
	{
		parse->token_list = lexer(input);
		parser(parse->token_list);
	}
	ft_lstiter(parse->token_list, print_list);
	get_token(parse);
	parser_state(parse);
	return (parse->token_list && parse->job_list ? 1 : 0);
}
