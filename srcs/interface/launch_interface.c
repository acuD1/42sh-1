/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_interactive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:29:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/29 13:46:26 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "log.h"
#include "parser.h"
#include "resolve.h"

static int8_t		is_input_valid(char *input_string)
{

	if (input_string == NULL
		|| ft_strlen(input_string) == 0
		|| (input_string[0] == 4 && input_string[1] == '\0')
		|| is_only_whitespaces(input_string) == TRUE)
		return (FALSE);
	return (TRUE);
}

void				launch_shell_prompt(t_registry *shell)
{
	char		*input_str;
	t_interface *itf;

	itf = &shell->interface;
	log_print(shell, LOG_INFO, "Starting prompt.\n");
	define_interface_signal_behavior(shell);
	while (1)
	{
		input_str = prompt(shell);
		init_parser(&shell->parser);
		shell->parser.env = shell->env;
		if (is_input_valid(input_str) == TRUE)
		{
			push_history_entry(&(itf->history_head),
							create_history_entry(itf->line->buffer));
			execution_pipeline(shell, input_str);
		}
		else if (is_eof(input_str) == TRUE)
				return ;
		cleanup_interface(shell);
	}
	cleanup_interface(shell);
	define_interface_default_signals(shell);
}

void				launch_interface(t_registry *shell)
{
	log_print(shell, LOG_INFO, "Starting interface.\n");
	if (fill_interface_data(shell) == SUCCESS)
		launch_shell_prompt(shell);
	else
		ft_printf("[CRITICAL] - Interface data could not be fetched.\n");
	restore_term_behavior(shell);
}
