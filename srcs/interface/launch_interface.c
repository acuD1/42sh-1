/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_interface.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:29:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/02 03:18:50 by cempassi         ###   ########.fr       */
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

	define_interface_signal_behavior(shell);
	if (get_input(shell, &input) == FAILURE)
	{
		cleanup_interface(shell);
		return (FAILURE);
	}
	ft_putchar('\n');
	update_history(shell, input);

//	define_execution_signals(shell);
	execution_pipeline(shell, lexer(&shell->lexinfo, input));
	return (SUCCESS);
}

void				launch_interface(t_registry *shell)
{
	log_print(shell, LOG_INFO, "Starting interface.\n");
	while (launch_shell_prompt(shell) == SUCCESS)
		cleanup_interface(shell);
	restore_term_behavior(shell);
}
