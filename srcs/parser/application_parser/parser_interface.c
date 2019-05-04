/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cempassi <cempassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:01:44 by cempassi          #+#    #+#             */
/*   Updated: 2019/05/04 16:06:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"
#include "lexer.h"

t_registry	*g_shell;

void	error_parser(t_parser *parse)
{
	parse->state = P_ERROR;
	if (parse->valid == -1)
		ft_dprintf(2, "21sh: OLDPWD is not set\n");
	else if (parse->valid == -2)
		ft_dprintf(2, "21sh: No such user or directory\n");
	else if (parse->valid == -3)
		ft_dprintf(2, "21sh: No such file\n");
	ft_stckdestroy(&parse->stack, del_token);
}

void	separator_parser(t_parser *parse)
{
	parse->state = P_SEPARATOR;
	get_token(parse);
}

void	stop_parser(t_parser *parse)
{
	t_list		*node;
	t_token		*token;

	parse->state = P_STOP;
	token = ft_stckpop(&parse->stack);
	parse->process.env = ft_lsttotab(parse->env, variable_to_str);
	node = ft_lstnew(&parse->process, sizeof(t_process));
	ft_lstaddback(&parse->job.process_list, node);
	node = ft_lstnew(&parse->job, sizeof(t_job));
	ft_lstaddback(&parse->job_list, node);
	free(token);
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
