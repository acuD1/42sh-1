/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_interactive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:29:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 01:11:08 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "line_edit.h"
#include "log.h"
#include "lexer.h"

static int8_t		allocate_data_structures(t_vector **vector,
				t_window **window, t_cursor **cursor)
{
	if ((*vector = ft_vctnew(0)) == NULL)
		return (-1);
	if ((*window = malloc(sizeof(t_window))) == NULL)
	{
		free(vector);
		return (-2);
	}
	if ((*cursor = malloc(sizeof(t_cursor))) == NULL)
	{
		free(window);
		free(vector);
		return (-3);
	}
	ft_memset(*window, 0, sizeof(t_window));
	ft_memset(*cursor, 0, sizeof(t_cursor));
	return (0);
}

int8_t				fill_interface_data(t_registry *shell)
{
	t_vector	*vector;
	t_window	*window;
	t_cursor	*cursor;

	if (allocate_data_structures(&vector, &window, &cursor) != 0)
		return (-3);
	shell->interface.line = vector;
	shell->interface.window = window;
	shell->interface.cursor = cursor;
	shell->interface.state = INT_PS1;
	if (init_window(shell, &shell->interface) != 0)
		return (-2);
	if (init_cursor(shell) != 0)
		return (-1);
	return (0);
}

static int8_t		is_input_valid(char *input_string)
{
	if (input_string == NULL)
		return (-1);
	if (ft_strequ(input_string, "exit") || input_string[0] == 4)
		return (-2);
	return (1);
}

void				launch_shell_prompt(t_registry *shell)
{
	char	*input;

	log_print(shell, LOG_INFO, "Starting prompt.\n");
	define_interface_signal_behavior(shell);
	while (1)
	{
		input = prompt(shell, &shell->interface);
		if (is_input_valid(input) == 1)
			lexer_parser(shell, input);
		else
			break ;
		cleanup_interface(shell);
	}
	define_interface_default_signals(shell);
}

void				shell_invoke_interactive(t_registry *shell)
{
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		log_print(shell, LOG_ERROR, "STDIN or STDOUT is not a valid tty.\n");
		return ;
	}
	log_print(shell, LOG_INFO, "Starting interactive mode.\n");
	if ((init_line_edition(shell)))
	{
// cleanup
		return ;
	}
	else
	{
		if (fill_interface_data(shell) == 0)
		{
			launch_shell_prompt(shell);
		}
		else
		{
//cleanup
		}
	}
	log_print(shell, LOG_INFO, "Restoring original shell behavior.\n");
	restore_term_behavior(shell);
	log_print(shell, LOG_INFO, "Releasing interface memory.\n");
	free_interface_registry(&shell->interface);
}
