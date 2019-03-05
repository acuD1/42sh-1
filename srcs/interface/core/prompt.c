/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/05 13:15:56 by skuppers         ###   ########.fr       */
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

//	log_print(reg, LOG_INFO, "Term size is %d rows ans %d columns.\n", window->rows, window->cols);

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
	//invoke sub-shell until it is valid
	validate_input_quoting(shell_reg, itf_registry);

	// ADD INPUT TO HISTORY (if QUOTING IS VALID)
	// Dont add if input is only  ' ' || '\n'
	if ((history_node = create_history_entry(itf_registry->vector->buffer)) != NULL)
	{
		if (itf_registry->history_head == NULL)
			itf_registry->history_head = history_node;
		else
			push_history_entry(&(itf_registry->history_head),
					history_node);
	}
	itf_registry->history_ptr = NULL;

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
	//	execute_shell_command(user_input_string);
		cleanup_interface_registry(itf_registry);
	//	ft_strdel(&user_input_string);
	}
}
