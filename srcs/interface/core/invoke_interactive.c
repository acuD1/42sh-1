/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_interactive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:29:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/24 02:58:15 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "line_edit.h"
#include "log.h"
#include "parser.h"
#include "resolve.h"

int8_t				fill_interface_data(t_registry *shell)
{
	if ((shell->interface.line = ft_vctnew(0)) == NULL)
		return (-1);
	shell->interface.state = INT_PS1;
	if (init_window(shell, &shell->interface) != 0)
		return (-2);
	if (init_cursor(shell) != 0)
		return (-1);
	return (0);
}

int					launch_shell_prompt(t_registry *shell)
{
	t_parser	parse;
	char		*input;

	log_print(shell, LOG_INFO, "Starting prompt.\n");
	init_parser(&parse);
	parse.env = shell->env;
	if ((input = prompt(shell, &shell->interface)))
	{
		if (ft_strequ(input, "exit") || input[0] == 4)
			return (0);
		if (lexer_parser(&parse, input))
			return (-1);
		//launch_job(shell, parse.job_list);
		return (1);
	}
	return (0);
}

void				shell_invoke_interactive(t_registry *shell)
{
	log_print(shell, LOG_INFO, "Starting interactive mode.\n");
	define_interface_signal_behavior(shell);
	if (init_line_edition(shell) || fill_interface_data(shell))
	{
		//cleanup
	}
	while(launch_shell_prompt(shell))
	{
		cleanup_interface(shell);
	}
	define_interface_default_signals(shell);
	log_print(shell, LOG_INFO, "Restoring original shell behavior.\n");
	restore_term_behavior(shell);
	log_print(shell, LOG_INFO, "Releasing interface memory.\n");
	free_interface_registry(&shell->interface);
}
