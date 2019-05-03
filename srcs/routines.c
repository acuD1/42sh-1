/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/03 04:29:43 by cempassi         ###   ########.fr       */
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

void		print_filedesc(t_list *lst)
{
	t_filedesc	*fd;

	fd = lst->data;
	if(fd->action & FD_CLOSE)
		ft_printf("Closing FD : %d\n", fd->first);
	else if (fd->action & FD_WRITE)
		ft_printf("FD : %d >>> FD : %d\n", fd->first, fd->second);
	else if (fd->action & FD_READ)
		ft_printf("FD : %d <<< FD : %d\n", fd->first, fd->second);
}

void		print_process(t_list *node)
{
	t_process	*process;

	process = node->data;
	ft_putchar('\n');
	ft_showtab(process->av);
	ft_lstiter(process->fd, print_filedesc);
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

void		init_job(t_job *job)
{
	ft_bzero(job, sizeof(t_job));
}

void		init_parser(t_registry *shell, t_parser *parse)
{
	ft_stckinit(&parse->stack);
	parse->state = P_START;
	parse->env = shell->env;
	init_process(&parse->process);
	init_job(&parse->job);
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
	if (token_list == NULL || parser(shell->graph, token_list) == FAILURE)
		return (FAILURE);
	////////////////////////////////// RETURN
	ft_bzero(&parse, sizeof(t_parser));
	parse.token_list = token_list;
	get_token(&parse);
	while (parse.token_list)
	{
		init_parser(shell, &parse);
		shell->current_job = parser_state(shell->parsing, &parse);
		if(parse.valid < 0)
		{
			delete_parser(&parse);
			continue;
		}

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
	}

	define_ign_signals();

	return (SUCCESS);
}

void		shell_exit_routine(t_registry *shell)
{
	if (shell->option.option & DEBUG_OPT)
		close(ft_atoi(get_intern_var(shell, INT_DBG_FD)));
	free_registry(shell);
}
