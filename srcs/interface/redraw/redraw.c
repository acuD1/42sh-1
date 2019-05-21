/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 10:14:06 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/21 16:16:42 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>
#include "log.h"
#include "interface_functions.h"

static void    redraw_line(t_registry *shell)
{
	t_coord		*co;
    uint64_t    rd_flag;
	uint64_t	prompt_len;
	uint64_t 	line_len = vct_len(shell->interface.line);
	uint64_t 	disp_len = vct_len(shell->interface.window.displayed_line);


	log_print(shell, LOG_INFO, "LL:%lu DL:%lu\n", line_len, disp_len);

	prompt_len = get_prompt_length(&shell->interface.prompt);
    rd_flag = shell->interface.window.rd_flag;

//    if (rd_flag & RD_ALL)
//    {
//		  tputs(shell->interface.termcaps.clear, 1, &ft_putc);
//        move_cursor_to_coord(&shell->interface, 0, 0);
//        print_prompt(shell, shell->interface.prompt.state);
//        print loop line
//    }

    if (rd_flag & RD_NONE)
        return;

	else if (rd_flag & RD_LINE)
    {
		co = index_to_coord(&shell->interface.window, prompt_len);
		move_cursor_to_coord(&shell->interface, co->x, co->y);

		int64_t	diff = line_len - disp_len;

		print_loop(&shell->interface, vct_get_string(shell->interface.line));
		if (diff < 0)
		{
			while (diff++ != 0)
				print_loop(&shell->interface, " ");
		}
    }
	else if (rd_flag & RD_LAST)
    {
		if (line_len >= disp_len) //added char
		{
			prompt_len += line_len - 1;
			co = index_to_coord(&shell->interface.window, prompt_len);
			move_cursor_to_coord(&shell->interface, co->x, co->y);
			print_char(&shell->interface,
							vct_charat(shell->interface.line,
							vct_len(shell->interface.line) - 1));
		}
		else //remove char
		{
			prompt_len += line_len - 1;
			co = index_to_coord(&shell->interface.window, prompt_len);
			move_cursor_to_coord(&shell->interface, co->x, co->y);
			print_char(&shell->interface, ' ');
		}
    }
	else if (rd_flag & RD_FPTE)
    {
		rd_flag &= ~RD_FPTE;
		rd_flag |= RD_FPTP;
		shell->interface.window.point2 =
				(line_len >= disp_len) ? line_len + 1 : disp_len + 1;
    }
	else if (rd_flag & RD_FSTP)
    {
		rd_flag &= ~RD_FSTP;
		rd_flag |= RD_FPTP;
		shell->interface.window.point1 = 0;
    }

	if (rd_flag & RD_FPTP)
    {
		co = index_to_coord(&shell->interface.window,
						shell->interface.window.point1
						+ prompt_len);

		move_cursor_to_coord(&shell->interface, co->x, co->y);

		int64_t length = (shell->interface.window.point2
							- shell->interface.window.point1) + 1;

		uint64_t tmp = shell->interface.window.point1;
		log_print(shell, LOG_INFO, "redrawing from %lu len %lu.\n", tmp, length);
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
}

void    redraw(t_registry *shell)
{
	redraw_line(shell);
	move_cursor(shell);

	vct_reset(shell->interface.window.displayed_line);
	vct_ncpy(shell->interface.window.displayed_line, shell->interface.line,
					vct_len(shell->interface.line));

	shell->interface.window.rd_flag = 0;
	shell->interface.window.point1 = 0;
	shell->interface.window.point2 = 0;
	shell->interface.window.point_cursor = 0;
}

inline void     set_redraw_flags(t_interface *itf, uint32_t rd_flag)
{
	itf->window.rd_flag = rd_flag;
}

inline void     set_redraw_bounds(t_interface *itf, uint64_t start, uint64_t end)
{
	itf->window.point1 = start;
	itf->window.point2 = end;
}

inline void     set_cursor_pos(t_interface *itf, uint64_t index)
{
	itf->window.point_cursor = index;
}
