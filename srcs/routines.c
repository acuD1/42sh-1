/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 07:18:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/29 13:28:47 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "21sh.h"
#include "log.h"
#include "interface_functions.h"
#include "parser.h"
#include "resolve.h"

int8_t		init_shell(t_registry *shell)
{
	init_debug_logger(shell);
	print_opt(shell);
	init_parsing(shell->parsing);
	generate_graph(shell);
	return (SUCCESS);
}

int8_t		execution_pipeline(t_registry *shell, char *command)
{
	log_print(shell, LOG_INFO, "Exec_pipeline processing: %s\n", command);
	ft_printf("\n---------------------------------\n");
	if (lexer_parser(&shell->parser, shell->graph, command) == SUCCESS)
	{
		ft_printf("\n---------------------------------\n");
		launch_job(shell, shell->parser.job_list);
		ft_lstdel(&shell->parser.job_list, delete_job);
		return (SUCCESS);
	}
	else
	{
		// parse error handling
		return (FAILURE);
	}
}

void	shell_exit_routine(t_registry *shell)
{
	if (shell->option.debug == TRUE)
		close(ft_atoi(get_intern_var(shell, INT_DBG_FD)));
}
