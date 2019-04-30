/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/30 15:35:15 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "log.h"
#include "interface_functions.h"
#include "parser.h"
#include "resolve.h"

void	print_process(t_list *node)
{
	t_process	*process;

	process = node->data;
	ft_putchar('\n');
	ft_showtab(process->av);
	ft_printf("FD : IN = %d | OUT = %d | ERROR = %d \n"
			,process->fd.in, process->fd.out, process->fd.err);
}

int8_t		init_shell(t_registry *shell)
{
	init_debug_logger(shell);
	print_opt(shell);
	init_parsing(shell->parsing);
	generate_graph(shell);
	return (SUCCESS);
}

void	init_job(t_job *job)
{
	ft_bzero(job, sizeof(t_job));
	job->fd.in = 0;
	job->fd.out = 1;
	job->fd.err = 2;
}

void	init_parser(t_registry *shell, t_parser *parse)
{
	ft_stckinit(&parse->stack);
	parse->state = P_START;
	parse->env = shell->env;
	init_process(&parse->process);
	init_job(&parse->job);
}

void	delete_parser(t_parser *parse)
{
	if (parse->tmp_env)
		ft_lstdel(&parse->tmp_env, NULL); //This will leak
	if (parse->job_list)
		ft_lstdel(&parse->job_list, delete_job);
}

int8_t	execution_pipeline(t_registry *shell, t_list *token_list)
{
	t_parser	parse;

	////////////////////// DEBUG LEXER ////////////////////////
	if ((shell->option.option & DEBUG_OPT) != FALSE)
	{
		ft_putendl("\n\n\033[34m-------------- LEXER ---------------");
		ft_lstiter(token_list, print_token);
		ft_putendl("------------------------------------\033[0m");
	}
	///////////////////////////////////////////////////////////

	if (!token_list || parser(shell->graph, token_list))
		return (FAILURE);
	ft_bzero(&parse, sizeof(t_parser));
	parse.token_list = token_list;
	get_token(&parse);
	while (parse.token_list)
	{
		init_parser(shell, &parse);
		parse.job_list = parser_state(shell->parsing, &parse);

		////////////////////// DEBUG PARSER ///////////////////////
		if ((shell->option.option & DEBUG_OPT) != FALSE)
		{
			ft_putstr("\n\033[33m-------------- PARSER --------------");
			ft_lstiter(((t_job*)(parse.job_list->data))->process_list,
							print_process);
			ft_putendl("------------------------------------\033[0m\n");
		}
		///////////////////////////////////////////////////////////

		launch_job(shell, parse.job_list);
		delete_parser(&parse);
	}
	return (SUCCESS);
}

void	shell_exit_routine(t_registry *shell)
{
	if (shell->option.option & DEBUG_OPT)
		close(ft_atoi(get_intern_var(shell, INT_DBG_FD)));
}
