/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invoke_interactive.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:29:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 16:35:03 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "log.h"
#include "parser.h"
#include "resolve.h"
/*
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
*/
int8_t				fill_interface_data(t_registry *shell, t_interface *itf)
{
	t_vector	*vector;
	t_window	window;
	t_cursor	cursor;

	if ((vector = ft_vctnew(0)) == NULL)
		return (FAILURE);
	ft_memset(&window, 0, sizeof(t_vector));
	ft_memset(&cursor, 0, sizeof(t_window));
	
//	if (allocate_data_structures(&vector, &window, &cursor) != 0)
//		return (-3);

	itf->line = vector;
	itf->window = &window;
	itf->cursor = &cursor;
	itf->state = INT_PS1;

	if (init_window(shell, &window) == FAILURE)
		return (FAILURE);
	if (init_cursor(shell) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static int8_t		is_input_valid(char *input_string)
{

	if (input_string == NULL
		|| ft_strlen(input_string) == 0
		|| (input_string[0] == 4 && input_string[1] == '\0')
		|| is_only_whitespaces(input_string) == TRUE)
		return (FAILURE);
	return (SUCCESS);
}

void				launch_shell_prompt(t_registry *shell, t_interface *itf)
{
	char	*input_str;
	int		ret_lexer_parser;

	log_print(shell, LOG_INFO, "Starting prompt.\n");
	define_interface_signal_behavior(shell);

	while (1)
	{
		ret_lexer_parser = FAILURE;
		input_str = prompt(shell, itf);
		init_parser(shell->parser);
		shell->parser->env = shell->env;
		if (is_input_valid(input_str) == SUCCESS)
		{
			push_history_entry(&(itf->history_head),
							create_history_entry(itf->line->buffer));
			ret_lexer_parser = lexer_parser(shell->parser, input_str);
		}
		else
		{
			if (is_eof(input_str) == TRUE)
				return ;
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
	t_interface itf;

	log_print(shell, LOG_INFO, "Starting interactive mode.\n");


	if ((load_interface(shell, &itf)) == FAILURE)
		ft_printf("[CRITICAL] - Interface setup failed.\n");
	else
	{
		if (fill_interface_data(shell, &itf) == SUCCESS)
			launch_shell_prompt(shell, &itf);
		else
			ft_printf("[CRITICAL] - Interface data could not be fetched.\n");
	}

	log_print(shell, LOG_INFO, "Restoring original shell behavior.\n");
	restore_term_behavior(shell);

	log_print(shell, LOG_INFO, "Releasing interface memory.\n");
	free_interface_registry(&itf);
//	free(&itf);
	//	unload_interface();
}