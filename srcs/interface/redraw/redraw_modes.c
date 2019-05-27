/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_modes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 10:26:30 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/27 16:34:28 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>
#include "interface_functions.h"

void	redrawmode_visual(__unused t_registry *shell)
{
	if (shell->interface.vis_start < 0
		|| shell->interface.vis_stop < 0
		|| (uint64_t)shell->interface.vis_start > vct_len(shell->interface.line) +1
		|| (uint64_t)shell->interface.vis_stop > vct_len(shell->interface.line) +1)
		return ;

	if (shell->interface.vis_stop < shell->interface.vis_start)
	{
		shell->interface.window.point1 = shell->interface.vis_stop;
		shell->interface.window.point2 = shell->interface.vis_start;
	}
	else
	{
		shell->interface.window.point1 = shell->interface.vis_start;
		shell->interface.window.point2 = shell->interface.vis_stop;
	}

	ft_dprintf(3, "|---> VISUAL MODE::Start:%d end:%d\n",
					shell->interface.window.point1,
					shell->interface.window.point2);

	redrawmode_line(shell);
	tputs(shell->interface.termcaps.standout_on, 1, &ft_putc);
	redrawmode_fptp(shell);
	tputs(shell->interface.termcaps.standout_off, 1, &ft_putc);
}

void	redrawmode_clear(t_registry *shell)
{
	tputs(shell->interface.termcaps.clear, 1, &ft_putc);
	shell->interface.cursor.x = 0;
	shell->interface.cursor.y = 0;
	shell->interface.cursor.index = 0;
	print_prompt(shell, shell->interface.prompt.state);
}

void	redrawmode_line(t_registry *shell)
{
	int64_t		diff;
	t_coord		*co;
	uint64_t	prompt_len;

	prompt_len = get_prompt_length(&shell->interface.prompt);
	co = index_to_coord(&shell->interface.window, prompt_len);
	move_cursor_to_coord(&shell->interface, co->x, co->y);

	diff = vct_len(shell->interface.line)
			- vct_len(shell->interface.window.displayed_line);
	print_loop(&shell->interface, vct_get_string(shell->interface.line));
	if (diff < 0)
	{
		while (diff++ != 0)
			print_loop(&shell->interface, " ");
	}
}

void	redrawmode_last(t_registry *shell)
{
	t_coord		*co;
	uint64_t	prompt_len;
	uint64_t 	line_len;
	uint64_t 	disp_len;

	line_len  = vct_len(shell->interface.line);
	disp_len  = vct_len(shell->interface.window.displayed_line);
	prompt_len = get_prompt_length(&shell->interface.prompt);

	if (line_len >= disp_len) //added char
	{
		prompt_len += line_len - 1;
		co = index_to_coord(&shell->interface.window, prompt_len);
//	ft_dprintf(3, "|-------Initial cursor movement----------|\n");
		move_cursor_to_coord(&shell->interface, co->x, co->y);
		print_char(&shell->interface,
							vct_charat(shell->interface.line,
						vct_len(shell->interface.line) - 1));
	}
	else //remove char
	{
		prompt_len += line_len - 1;
		co = index_to_coord(&shell->interface.window, prompt_len);
//	ft_dprintf(3, "|-------Initial cursor movement----------|\n");
		move_cursor_to_coord(&shell->interface, co->x, co->y);
		print_char(&shell->interface, ' ');
	}
}
#include "log.h"
void	redrawmode_fptp(t_registry *shell)
{
	t_coord		*co;
	uint64_t	prompt_len;
	uint64_t 	line_len;
	uint64_t 	disp_len;

	line_len  = vct_len(shell->interface.line);
	disp_len  = vct_len(shell->interface.window.displayed_line);
	prompt_len = get_prompt_length(&shell->interface.prompt);

	co = index_to_coord(&shell->interface.window,
					shell->interface.window.point1
					+ prompt_len);

	move_cursor_to_coord(&shell->interface, co->x, co->y);

	int64_t length = (shell->interface.window.point2);
	length -= shell->interface.window.point1;

	uint64_t tmp = shell->interface.window.point1;
	log_print(shell, LOG_INFO, "|--> FPTP Redrawing from %lu len %lu.\n", tmp, length);

	while (length > 0)
	{
		char c;
		if ((c = vct_charat(shell->interface.line, tmp)) == 0)
			print_char(&shell->interface, ' ');

		print_char(&shell->interface, c);
		++tmp;
		--length;
	}
}
