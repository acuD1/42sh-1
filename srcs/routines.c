/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/04 19:02:51 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "parser.h"
#include "log.h"
#include "sig.h"
#include "lexer.h"
#include "resolve.h"
#include <unistd.h>

void		init_process(t_process *process)
{
	ft_bzero(process, sizeof(t_process));
}

int8_t		init_shell(t_registry *shell)
{
	g_shell = shell;
	init_debug_logger(shell);
	print_opt(shell);
	init_parsing(shell->parsing);
	generate_graph(shell);
	init_lexinfo(shell);
	return (SUCCESS);
}

void		init_parser(t_registry *shell, t_parser *parse)
{
	ft_stckinit(&parse->stack);
	parse->state = P_START;
	parse->env = shell->env;
	init_process(&parse->process);
	ft_bzero(&parse->job, sizeof(t_job));
}

int8_t		execution_pipeline(t_registry *shell, t_list *token_list)
{
	t_parser	parse;


	define_parser_signals();

	////////////////////// DEBUG LEXER ////////////////////////
	if ((shell->option.option & DEBUG_OPT) != FALSE)
	{
		ft_putendl("\n\n\033[34m-------------- LEXER ---------------");
		ft_lstiter(token_list, print_token);
		ft_putendl("------------------------------------\033[0m");
	}
	///////////////////////////////////////////////////////////
	////////////////////////////////// RETURN
	ft_bzero(&parse, sizeof(t_parser));
	parse.token_list = token_list;
	while (parse.token_list)
	{
		if (parser(shell->graph, parse.token_list) == FAILURE)
		{
			free_token_list(token_list);
			return (FAILURE);
		}
		init_parser(shell, &parse);
		shell->current_job = parser_state(shell->parsing, &parse);
		////////////////////// DEBUG PARSER ///////////////////////
		if ((shell->option.option & DEBUG_OPT) != FALSE)
		{
			ft_putstr("\n\033[33m-------------- PARSER --------------");
			ft_lstiter(((t_job*)(parse.job_list->data))->process_list,
					print_process);
			ft_putendl("------------------------------------\033[0m\n");
		}
		///////////////////////////////////////////////////////////
		if(parse.valid <= 0)
		{
			delete_parser(&parse);
			continue;
		}
		launch_job(shell, parse.job_list);
		delete_parser(&parse);
	}

	define_ign_signals();

	return (SUCCESS);
}

void		shell_exit_routine(t_registry *shell)
{
	if ((shell->option.option & DEBUG_OPT) != FALSE)
		close(ft_atoi(get_intern_var(shell, INT_DBG_FD)));
	free_registry(shell);
}
