/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_interactive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:29:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/26 18:55:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "line_edit.h"
#include "log.h"
#include "parser.h"
#include "resolve.h"

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

int8_t				fill_interface_data(t_registry *shell, t_interface *itf)
{
	t_vector	*vector;
	t_window	*window;
	t_cursor	*cursor;

	if (allocate_data_structures(&vector, &window, &cursor) != 0)
		return (-3);
	itf->line = vector;
	itf->window = window;
	itf->cursor = cursor;
	itf->state = INT_PS1;
	if (init_window(shell, itf) != 0)
		return (-2);
	if (init_cursor(shell) != 0)
		return (-1);
	return (0);
}

static int8_t		is_input_valid(char *input_string)
{
	if (ft_strequ(input_string, "exit") || input_string[0] == 4)
		return (-2);
	if (input_string == NULL || ft_strequ(input_string, " ") || ft_strlen(input_string) == 0)
		return (-1);
	return (1);
}

void				launch_shell_prompt(t_registry *shell, t_interface *itf)
{
	t_parser parse;
	int8_t	valid;
	char	*user_input_string;

	log_print(shell, LOG_INFO, "Starting prompt.\n");
	define_interface_signal_behavior(shell);
	valid = 0;
	while (1)
	{
		init_parser(&parse);
		parse.env = shell->env;
		user_input_string = prompt(shell, itf);
		valid = is_input_valid(user_input_string);
		if (valid == 1)
		{
			push_history_entry(&(itf->history_head), create_history_entry(itf->line->buffer));
			lexer_parser(&parse, user_input_string);
		}
		else if (valid == -1)
		{
			cleanup_interface(shell);
			continue ;
		}
		else
			break ;
		cleanup_interface(shell);
		launch_job(shell, parse.job_list);
		ft_lstdel(&parse.job_list, delete_job);
	}
	define_interface_default_signals(shell);
}

void				shell_invoke_interactive(t_registry *shell)
{
	t_interface *itf;

	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO))
	{
		log_print(shell, LOG_ERROR, "STDIN or STDOUT is not a valid tty.\n");
		return ;
	}
	log_print(shell, LOG_INFO, "Starting interactive mode.\n");
	if ((itf = init_line_edition(shell)) == NULL)
	{
		ft_printf("[CRITICAL] - Line edition failed.\n");
		return ;
	}
	else
	{
		if (fill_interface_data(shell, itf) == 0)
		{
			launch_shell_prompt(shell, itf);
		}
		else
		{
			ft_printf("[CRITICAL] - Interface data could not be fetched.\n");
		}
	}
	log_print(shell, LOG_INFO, "Restoring original shell behavior.\n");
	restore_term_behavior(shell);
	log_print(shell, LOG_INFO, "Releasing interface memory.\n");
	free_interface_registry(itf);
	free(itf);
}
