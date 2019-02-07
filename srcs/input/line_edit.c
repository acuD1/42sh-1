/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 14:41:16 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/07 18:44:13 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "log.h"
#include "ft_printf.h"

int			ak_keycodes[AK_AMOUNT][READ_SIZE];
t_buffer	*g_clipboard;

void	clean_ak_keycodes(void)
{
	int y;
	int x;

	y = 0;
	while (y < AK_AMOUNT)
	{
		x = 0;
		while (x < READ_SIZE)
		{
			ak_keycodes[y][x] = 0;
			++x;
		}
		++y;
	}
}

void	init_ak_keycodes(void)
{
	clean_ak_keycodes();
	init_ak_enter();
	init_ak_arrow_right();
	init_ak_arrow_left();
	init_ak_arrow_up();
	init_ak_arrow_down();
	init_ak_home();
	init_ak_end();
	init_ak_backspace();
	init_ak_delete();
	init_ak_ctrl_a();
	init_ak_ctrl_c();
	init_ak_ctrl_d();
	init_ak_ctrl_e();
	init_ak_ctrl_l();
	init_ak_ctrl_x();
	init_ak_ctrl_b();
	init_ak_ctrl_p();
	init_ak_ctrl_lb();
	init_ak_ctrl_rb();
	init_ak_ctrl_r();
	init_ak_ctrl_f();
	init_ak_ctrl_left();
	init_ak_ctrl_right();
}

void	init_line_edition(char **environ)
{
	char			*term_name;
	struct termios	t_term;
	(void)environ;

	if ((term_name = getenv("TERM")) == NULL)
		log_print(LOG_CRITICAL, "Terminal not found.\n");
	if ((tgetent(NULL, term_name)) == -1)
		log_print(LOG_ERROR, "Tgetent failed.\n");

	//TODO: FIX I/O ?
	if (isatty(STDIN_FILENO))
	{
		if ((tcgetattr(STDIN_FILENO, &t_term)) == -1)
			log_print(LOG_ERROR, "Tcgetattr failed saving info.\n");
		else
			log_print(LOG_OK, "Reached targeting terminal.\n");
	}
	else
		log_print(LOG_WARNING, "STDIN is not a valid tty.\n");

	t_term.c_lflag &= ~(ICANON);
	t_term.c_lflag &= ~(ECHO);
	t_term.c_cc[VMIN] = 1;
	t_term.c_cc[VTIME] = 0;
	if (isatty(STDIN_FILENO))
		if (tcsetattr(STDIN_FILENO, TCSANOW, &t_term) == -1)
			log_print(LOG_ERROR, "Tcsetattr failed setting params.\n");

	init_termcap_calls();
	init_termcap_actions(tc_call);

	log_print(LOG_INFO, "Termcaps functions up & ready.\n");

	init_ak_keycodes();

	log_print(LOG_INFO, "Keycodes set.\n");

	g_clipboard = malloc(sizeof(t_buffer));
	g_clipboard->current_size = CLIPBOARD_SIZE;
	g_clipboard->buffer = ft_strnew(CLIPBOARD_SIZE);
	log_print(LOG_INFO, "Clipboard initialized.\n");

	log_print(LOG_OK, "Line edition initialized.\n");
}
