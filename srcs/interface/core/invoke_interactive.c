/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_interactive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:29:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/04 14:12:20 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"

void	launch_shell_prompt(t_registry *shell_registry,
		t_interface_registry *itf_registry)
{
	char	*user_input_string;

	log_print(shell_registry, LOG_INFO, "Starting prompt.\n");
	define_interface_signal_behavior(itf_registry, shell_registry);
	while (1)
	{
		user_input_string = prompt(shell_registry, itf_registry);
		if (user_input_string == NULL)
			return ;
		if (ft_strequ(user_input_string, "exit") || user_input_string[0] == 4)
			return ;
		log_print(shell_registry, LOG_INFO, "Sending: |%s|\n", user_input_string);
		// Call execution here
		cleanup_interface_registry(itf_registry);
		//ft_strdel(&user_input_string);
	}
	define_interface_default_signals(shell_registry);
}

void	shell_invoke_interactive(t_registry *shell_registry)
{
	t_interface_registry *itf_registry;

	log_print(shell_registry, LOG_INFO, "Starting interactive mode.\n");
	itf_registry = init_line_edition(shell_registry);
	if (itf_registry != NULL)
	{
		launch_shell_prompt(shell_registry, itf_registry);
		log_print(shell_registry, LOG_INFO, "Shell is now shutting down.\n");
		close(ft_atoi(get_intern_var(shell_registry, INT_DBG_FD)));
		log_print(shell_registry, LOG_INFO, "Restoring original shell behavior.\n");
		restore_original_term_behavior(shell_registry, itf_registry);
		log_print(shell_registry, LOG_INFO, "Releasing memory.\n");
		free_interface_registry(itf_registry);
		free(itf_registry);
	}
	else
	{
		log_print(shell_registry, LOG_CRITICAL,
				"Line edition failed, shutting down.\n");
		ft_dprintf(2, "\n");
	}
}
