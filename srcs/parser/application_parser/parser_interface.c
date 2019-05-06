/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:01:44 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/05 19:12:26 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"
#include "lexer.h"

void	error_parser(t_parser *parse)
{
	t_token		*token;

	parse->state = P_ERROR;
	parse->token.type = E_DEFAULT;
	parse->valid = -1;
	if (parse->token_list && (token = (t_token *)(parse->token_list->data)))
	{
		while (token->type != E_SEMICOLON && token->type != E_PIPE
				&& token->type != E_END)
		{
			ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
			get_token(parse);
			token = (t_token *)(parse->token_list->data);
			if (token == NULL)
				break ;
		}
	}
	if (parse->token_list && token != NULL && (token->type == E_SEMICOLON
			|| token->type == E_PIPE))
	{
		ft_stckpush(&parse->stack, &parse->token, sizeof(t_token));
		get_token(parse);
	}
	ft_lstdel(&parse->process.fd, close_fd);
}

void	separator_parser(t_parser *parse)
{
	parse->state = P_SEPARATOR;
}

void	stop_parser(t_parser *parse)
{
	t_list		*node;

	parse->state = P_STOP;
	node = ft_lstnew(&parse->process, sizeof(t_process));
	ft_lstaddback(&parse->job.process_list, node);
	node = ft_lstnew(&parse->job, sizeof(t_job));
	ft_lstaddback(&parse->job_list, node);
	parse->token.type = E_DEFAULT;
	parse->valid = 1;
}

void	end_parser(t_parser *parse)
{
	t_list		*node;

	parse->state = P_END;
	node = ft_lstnew(&parse->process, sizeof(t_process));
	ft_lstaddback(&parse->job.process_list, node);
	node = ft_lstnew(&parse->job, sizeof(t_job));
	ft_lstaddback(&parse->job_list, node);
	get_token(parse);
	parse->valid = 1;
}
