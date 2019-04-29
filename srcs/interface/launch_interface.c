/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:29:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/29 15:12:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "log.h"
#include "parser.h"
#include "resolve.h"

void				update_history(t_registry *shell, char *input)
{
	t_history	*new;

	new = create_history_entry(input);
	push_history_entry(&shell->interface.history_head, new);
}

int					get_input(t_registry *shell, char **input)
{
	*input = prompt(shell);
	if (*input == NULL || **input == '\0')
		return (get_input(shell, input));
	else if (is_eof(*input))
		return (FAILURE);
	return (SUCCESS);
}

int					launch_shell_prompt(t_registry *shell)
{
	char		*input;

	log_print(shell, LOG_INFO, "Starting prompt.\n");
	if(get_input(shell, &input))
	{
		cleanup_interface(shell);
		return (FAILURE);
	}
	update_history(shell, input);
	execution_pipeline(shell, lexer(input));
	return (SUCCESS);
}

void				launch_interface(t_registry *shell)
{
	define_interface_signal_behavior(shell);
	while (launch_shell_prompt(shell) == SUCCESS)
		cleanup_interface(shell);
	define_interface_default_signals(shell);
	log_print(shell, LOG_INFO, "Starting interface.\n");
	restore_term_behavior(shell);
}
