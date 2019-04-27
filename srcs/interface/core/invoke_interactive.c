/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_interactive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:29:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 16:24:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
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
	if (input_string == NULL || ft_strequ(input_string, " ")
		|| ft_strlen(input_string) == 0 || input_string[0] == 4)
		return (FAILURE);
	return (SUCCESS);
}

void				launch_shell_prompt(t_registry *shell, t_interface *itf)
{
	char	*user_input_string;
	int		ret_lexer_parser;

	log_print(shell, LOG_INFO, "Starting prompt.\n");

	define_interface_signal_behavior(shell);

	while (1)
	{
		ret_lexer_parser = FAILURE;

		// prompt
		user_input_string = prompt(shell, itf);

		//TODO: Check if input is not NULL and not len=0
		//		Check if input is EOF
		//		Check if input is only whitespaces and/or IFS
		if (is_input_valid(user_input_string) == SUCCESS)
		{
			push_history_entry(&(itf->history_head), create_history_entry(itf->line->buffer));
			ret_lexer_parser = lexer_parser(shell->parser, user_input_string);
		}
		else
		{
			cleanup_interface(shell);
			continue ;
		}
		cleanup_interface(shell);
		if (ret_lexer_parser == SUCCESS)
		{
			launch_job(shell, shell->parser->job_list);
			ft_lstdel(&shell->parser->job_list, delete_job);
		}
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
		if (fill_interface_data(shell, itf) == SUCCESS)
			launch_shell_prompt(shell, itf);
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
