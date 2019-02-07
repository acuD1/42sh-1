/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:49:54 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/07 17:32:29 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "libft.h"
#include "ft_printf.h"
#include "log.h"

#include <sys/ioctl.h>
#include "history.h"

//t_history	*g_history_head;
t_buffer	*g_vector;
t_winsize	*g_ws;

static t_buffer	*init_buffer_struct(void)
{
	t_buffer *buffer_struct;

	buffer_struct = malloc(sizeof(t_buffer));
	buffer_struct->buffer = ft_strnew(LINE_BUFFER_SIZE);
	buffer_struct->current_size = LINE_BUFFER_SIZE;
	return (buffer_struct);
}

void	handle_resize(int signo)
{
	struct winsize w;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
		log_print(LOG_ERROR, "Terminal size could not be updated.\n");
	g_ws->cols = w.ws_col;
	g_ws->rows = w.ws_row;
	ft_printf_fd(2, "Changed term size to %d rows, %d cols.\n", g_ws->rows, g_ws->cols);
	redraw_input_line(g_vector, g_ws);
}

void	init_signal_handler(t_buffer *vector, t_winsize *ws)
{
	g_vector = vector;
	g_ws = ws;
	if (signal(SIGWINCH, handle_resize) == SIG_ERR)
	{
		log_print(LOG_CRITICAL, "Error catching the resize signal.\n");
		exit (42);
	}
}

static t_winsize *init_win_struct(void)
{
	struct winsize	w;
	t_winsize		*winsize;


	winsize = malloc(sizeof(t_winsize));
	winsize->cursor_index = 0;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &w) == -1)
		log_print(LOG_CRITICAL, "Terminal size could not be determined!\n");
	winsize->x = PROMPT_TEXT_LENGTH; //prompt length
	winsize->y = 0;
	winsize->cols = w.ws_col;
	winsize->rows = w.ws_row;
	winsize->cursor_index = 0;
		log_print(LOG_INFO, "Term size is %d rows ans %d columns.\n", winsize->rows, winsize->cols);
	return (winsize);
}

void	reinit_variables(t_buffer *vect, t_winsize *ws)
{
	ft_strdel(&vect->buffer);
	vect->current_size = LINE_BUFFER_SIZE;
	vect->buffer = ft_strnew(LINE_BUFFER_SIZE);
	free(ws);
	ws = init_win_struct();
	g_vector = vect;
	g_ws = ws;
}

void	prompt(void)
{
	char			character[READ_SIZE + 1];
	t_buffer		*buffer_vector;
	t_winsize		*ws;

	//	g_history_head = NULL;

	buffer_vector = init_buffer_struct();

	while (1)
	{
		ws = init_win_struct();
		init_signal_handler(buffer_vector, ws);

		ft_bzero(character, READ_SIZE);
		ft_bzero(buffer_vector->buffer, buffer_vector->current_size);
		ft_printf_fd(1, "\n%s", PROMPT_TEXT);
		ws->y = 0;
		while (character[0] != 10) //reading until nl
		{
			ft_bzero(character, READ_SIZE);
			if (read(0, character, READ_SIZE) == -1)
			{
				log_print(LOG_CRITICAL, "Read failed.\n");
				exit(42);
			}
			ws->cursor_index = handle_input_key(character, buffer_vector, ws);
		}
		ft_printf_fd(1, "\nLine edition sending: |%s|\n", buffer_vector->buffer);


		//Input is passed here
		//parsing
		// ADD INPUT TO HISTORY (if QUOTING IS VALID)
		//		push_history_entry(&g_history_head, create_history_entry(buffer_vector->buffer));
		//execution
	}
}
