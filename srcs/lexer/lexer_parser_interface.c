/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_interface.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 22:31:09 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/20 01:33:11 by cempassi         ###   ########.fr       */
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
	process->fdin = 0;
	process->fdout = 1;
	process->fderror = 2;
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

t_list	*lexer_parser(t_registry *shell, char *input)
{
	t_parser	parse;

	if (!*input)
		return (NULL);
	init_parser(&parse);
	parse.token_list = lexer(input);
	parse.env = shell->env;
	get_token(&parse);
	parser(parse.token_list);
	parser_state(&parse);
	return (parse.job_list);
}
