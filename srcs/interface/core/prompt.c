/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/26 15:29:30 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"
#include "log.h"
#include "21sh.h"
#include <sys/ioctl.h>
#include "history.h"

static t_winsize *init_win_struct(t_registry *reg, t_winsize *window)
{
	struct winsize	w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
	{
		log_print(reg, LOG_ERROR, "Terminal size could not be determined!\n");
		return (NULL);
	}

	window->cursor_index = 0;
	window->x = PROMPT_TEXT_LENGTH;
	window->y = 0;
	window->cols = w.ws_col;
	window->rows = w.ws_row;

	window->max_line_len = ((window->cols * window->rows) - (PROMPT_TEXT_LENGTH + 3));

	return (window);
}

char	*prompt(t_registry *shell_reg, t_interface_registry *itf_registry)
{
	char			character[READ_SIZE + 1];
	t_vector		*vector;
	t_winsize		*window;
	t_history		*history_node;

	vector = NULL;
	window = NULL;
	if ((vector = ft_vctnew(0)) == NULL
			|| ((window = malloc(sizeof(t_winsize))) == NULL))
	{
		log_print(shell_reg, LOG_CRITICAL, "Error allocating interface memory.\n");
		return (NULL);
	}

	itf_registry->interface_state = PS1;

	if (!(init_win_struct(shell_reg, window)))
		return (NULL);
	itf_registry->window = window;
	itf_registry->vector = vector;

	ft_bzero(character, READ_SIZE);
	ft_dprintf(STDOUT_FILENO, "\n%s", PROMPT_TEXT);

	history_node = NULL;

	while (character[0] != IFS_CHARACTER)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(shell_reg, vector);
			return (NULL);
		}
		window->cursor_index = handle_input_key(character, itf_registry);

		/* Ctrl+D EOF handling*/
		if (vector->buffer[0] == 4)
			return (vector->buffer);
	}

	/* Anti-input overwrite */
	window->cursor_index = tc_ak_end(itf_registry);

	//check quoting
	//invoke sub-prompt until it is valid
	validate_input_quoting(shell_reg, itf_registry);

	// ADD INPUT TO HISTORY (if QUOTING IS VALID)
	// Dont add if input is only  ' ' || '\n'
/*	if ((history_node = create_history_entry(
					trim_ifs(itf_registry->vector->buffer, "\n"))) != NULL)
	{
		log_print(shell_reg, LOG_OK, "Created history entry with data: |%s|\n",
			history_node->command);

		if (itf_registry->history_head == NULL)
			itf_registry->history_head = history_node;
		else
			push_history_entry(&(itf_registry->history_head),
					history_node);
	}
	itf_registry->history_ptr = NULL;*/

	log_print(shell_reg, LOG_INFO, "Line edition sending: |%s|\n", itf_registry->vector->buffer);

	return (itf_registry->vector->buffer);
}

void	launch_shell_prompt(t_registry *shell_registry,
		t_interface_registry *itf_registry)
{
	char					*user_input_string;

	log_print(shell_registry, LOG_INFO, "Starting prompt.\n");
	define_interface_signal_behavior(itf_registry, shell_registry);
	while (1)
	{
		user_input_string = prompt(shell_registry, itf_registry);
		if (ft_strequ(user_input_string, "exit") || user_input_string[0] == 4)
			return ;
//		if (ft_strequ == '\n') continue;
	//	execute_shell_command(user_input_string);
		cleanup_interface_registry(itf_registry);
	//	ft_strdel(&user_input_string);
	}
}

void				shell_invoke_interactive(t_registry *shell_registry)
{
	t_interface_registry *itf_registry;

	itf_registry = init_line_edition(shell_registry);
	if (itf_registry != NULL)
	{
		launch_shell_prompt(shell_registry, itf_registry);
		//restore_original_term_behavior(shell_registry, itf_registry);
		free_interface_registry(itf_registry);
		free(itf_registry);
	}
	else
		log_print(shell_registry, LOG_CRITICAL, "Line edition failed, shuting down.\n");
}

