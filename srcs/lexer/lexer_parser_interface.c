/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_interface.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 22:31:09 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/26 16:04:33 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	print_process(t_list *node)
{
	t_process	*process;

	process = node->data;
	ft_showtab(process->av);
	ft_printf("FD : IN = %d | OUT = %d | ERROR = %d \n"
			,process->fd.in, process->fd.out, process->fd.err);
}

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

void	init_job(t_job *job)
{
	ft_bzero(job, sizeof(t_job));
	job->fd.in = 0;
	job->fd.out = 1;
	job->fd.err = 2;
}

void	init_parser(t_parser *parse)
{
	ft_bzero(parse, sizeof(t_parser));
	parse->state = P_START;
	bzero_parsing(parse);
	init_parsing(parse);
	ft_stckinit(&parse->stack);
	init_process(&parse->process);
	init_job(&parse->job);
}

int		lexer_parser(t_parser *parse, char *input)
{
	if (!*input)
		return (0);
	if (!parse->token_list)
	{
		parse->token_list = lexer(input);
		ft_putchar('\n');
		ft_lstiter(parse->token_list, print_token);
		if (parser(parse->token_list))
			return (-1);
	}
	get_token(parse);
	parser_state(parse);
	ft_lstiter(((t_job*)(parse->job_list->data))->process_list, print_process);
	return (parse->token_list && parse->job_list ? 1 : 0);
}
