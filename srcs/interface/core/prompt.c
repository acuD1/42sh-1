/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/03/01 15:08:41 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"
#include "log.h"
#include "21sh.h"
#include <sys/ioctl.h>
#include "history.h"

/*
void	handle_resize(int signo)
{
	struct winsize w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1) ;
	//log_print(LOG_ERROR, "Terminal size could not be updated.\n");
	g_ws->cols = w.ws_col;
	g_ws->rows = w.ws_row;
	//	ft_printf_fd(2, "Changed term size to %d rows, %d cols.\n", g_ws->rows, g_ws->cols);
	redraw_input_line(g_vector, g_ws);
}

static void	init_signal_handler(t_registry *reg, t_vector *vector, t_winsize *ws)
{
	g_vector = vector;
	g_ws = ws;
	if (signal(SIGWINCH, handle_resize) == SIG_ERR)
	{
		log_print(reg, LOG_CRITICAL, "Error catching the resize signal.\n");
		exit (42);
	}
}


void	reinit_variables(t_registry *reg, t_vector *vect, t_winsize *ws)
{

	ft_vctreset(vect);
	free(ws);
	ws = init_win_struct(reg);
	g_ws = ws;
}
*/
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

	log_print(reg, LOG_INFO, "Term size is %d rows ans %d columns.\n", window->rows, window->cols);

	return (window);
}

char	*prompt(t_registry *shell_reg, t_interface_registry *itf_registry)
{
	char			character[READ_SIZE + 1];
	t_vector		*vector;
	t_winsize		*window;

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


//TODO: refactor & signals
//	init_signal_handler(shell_reg, vector, ws);


	ft_bzero(character, READ_SIZE);
	log_print(shell_reg, LOG_INFO, "Starting prompt.\n");
	ft_printf_fd(1, "\n%s", PROMPT_TEXT);

	while (character[0] != NEWLINE_KEYCODE)
	{
		ft_bzero(character, READ_SIZE);
		if (read(0, character, READ_SIZE) == -1)
		{
			prompt_read_failed(shell_reg, vector);
			return (NULL);
		}
		window->cursor_index = handle_input_key(character, itf_registry);
	}

	//check quoting
	//invoke sub-shell until it is valid

	// ADD INPUT TO HISTORY (if QUOTING IS VALID)
	//push_history_entry(&g_history_head, create_history_entry(buffer_vector->buffer));

	log_print(shell_reg, LOG_INFO, "Line edition sending: |%s|\n", vector->buffer);

	return (ft_strdup(vector->buffer));
}

void	launch_shell_prompt(t_registry *shell_registry,
		t_interface_registry *itf_registry)
{
	char					*user_input_string;

	define_interface_signal_behavior(itf_registry, shell_registry);
	while (1)
	{
		user_input_string = prompt(shell_registry, itf_registry);
		if (ft_strequ(user_input_string, "exit"))
			return ;
	//	execute_shell_command(user_input_string);
		ft_strdel(&user_input_string);
	}
}
