/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:01:44 by cempassi          #+#    #+#             */
/*   Updated: 2019/04/26 18:08:26 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"


void	error_parser(t_parser *parse)
{
	ft_printf("Error on token type %d\n",parse->token.type);
	parse->state = P_ERROR;
}

void	separator_parser(t_parser *parse)
{
	parse->state = P_SEPARATOR;
	get_token(parse);
}

void	stop_parser(t_parser *parse)
{
	t_list		*node;

	parse->state = P_STOP;
	parse->process.env = ft_lsttotab(parse->env, variable_to_str);
	node = ft_lstnew(&parse->process, sizeof(t_process));
	ft_lstaddback(&parse->job.process_list, node);
	node = ft_lstnew(&parse->job, sizeof(t_job));
	ft_lstaddback(&parse->job_list, node);
}

void	end_parser(t_parser *parse)
{
	t_list		*node;

	parse->state = P_END;
	parse->process.env = ft_lsttotab(parse->env, variable_to_str);
	node = ft_lstnew(&parse->process, sizeof(t_process));
	ft_lstaddback(&parse->job.process_list, node);
	node = ft_lstnew(&parse->job, sizeof(t_job));
	ft_lstaddback(&parse->job_list, node);
	++parse->valid;
}
