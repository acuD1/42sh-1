/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 10:14:06 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/18 16:24:26 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <termcap.h>
#include "interface_functions.h"

static void     move_cursor_to_coord(t_interface *itf, uint64_t x, uint64_t y)
{
    int64_t x_moves;
    int64_t y_moves;

    x_moves =  ((itf->cursor.x - x) * (-1));
    y_moves =  ((itf->cursor.y - y) * (-1));

	if (y_moves > 0)
		while (y_moves-- > 0)
    	    tputs(itf->termcaps.down, 1, &ft_putc);

	if (y_moves < 0)
	    while (y_moves++ < 0)
    	    tputs(itf->termcaps.up, 1, &ft_putc);

	if (x_moves > 0)
	    while (x_moves-- > 0)
    	    tputs(itf->termcaps.left, 1, &ft_putc);

	if (x_moves < 0)
	    while (x_moves++ < 0)
    	    tputs(itf->termcaps.right, 1, &ft_putc);

	itf->cursor.x = x;
	itf->cursor.y = y;
}

static void    redraw_line(t_registry *shell)
{
    uint64_t    rd_flag;

    rd_flag = shell->interface.window.rd_flag;
    if (rd_flag & RD_NONE)
        return;
    if (rd_flag & RD_ALL)
    {
		tputs(shell->interface.termcaps.clear, 1, &ft_putc);
        move_cursor_to_coord(&shell->interface, 0, 0);
        print_prompt(shell, shell->interface.prompt.state);
    }
    if (rd_flag & RD_LINE)
    {
		uint32_t plen = get_prompt_length(&shell->interface.prompt);
		t_coord *co = index_to_coord(&shell->interface.window, plen);
		move_cursor_to_coord(&shell->interface, co->x, co->y);

		int64_t	diff = vct_len(shell->interface.line)
				- vct_len(shell->interface.window.displayed_line);

		if (diff < 0)
		{
			print_loop(&shell->interface, vct_get_string(shell->interface.line));
			while (diff++ != 0)
				print_loop(&shell->interface, " ");
		}
		else
			print_loop(&shell->interface, vct_get_string(shell->interface.line));
    }
    if (rd_flag & RD_LAST)
    {
		uint32_t plen = get_prompt_length(&shell->interface.prompt)
						+ vct_len(shell->interface.line);

		t_coord *co = index_to_coord(&shell->interface.window, plen);

		move_cursor_to_coord(&shell->interface, co->x, co->y);

	char c = vct_charat(shell->interface.line, vct_len(shell->interface.line) - 1);
//	ft_dprintf(2, "char|%c|\n", c);
		print_char(&shell->interface, c);

		if (vct_len(shell->interface.line)
						< vct_len(shell->interface.window.displayed_line))
			print_char(&shell->interface, ' ');
    }

    if (rd_flag & RD_FPTE)
    {
		rd_flag &= ~RD_FPTE;

		shell->interface.window.point2 = vct_len(shell->interface.line);

		rd_flag |= RD_FPTP;
    }

    if (rd_flag & RD_FSTP)
    {
		rd_flag &= ~RD_FSTP;

		shell->interface.window.point1 = 0;

		rd_flag |= RD_FPTP;
    }

	if (rd_flag & RD_FPTP)
    {
		t_coord *co1 = index_to_coord(&shell->interface.window,
						shell->interface.window.point1
						+ get_prompt_length(&shell->interface.prompt));

		move_cursor_to_coord(&shell->interface, co1->x, co1->y);

		int64_t length = (shell->interface.window.point2
							- shell->interface.window.point1) + 1;

		int tmp = shell->interface.window.point1;
		while (length > 0)
		{
			print_char(&shell->interface,
							vct_charat(shell->interface.line, tmp++));
			--length;
		}
    }
}

static void     move_cursor(t_registry *shell)
{
	t_coord		*coord;
    uint64_t    rd_flag;

	coord = NULL;
    rd_flag = shell->interface.window.rd_flag;
    if (rd_flag & RD_CEND)
    {
		coord = index_to_coord(&shell->interface.window,
								get_prompt_length(&shell->interface.prompt)
								+ vct_len(shell->interface.line) + 1);
		move_cursor_to_coord(&shell->interface, coord->x, coord->y);
		shell->interface.cursor.index = vct_len(shell->interface.line);
    }
    else if (rd_flag & RD_CHOME)
    {
		coord = index_to_coord(&shell->interface.window,
								get_prompt_length(&shell->interface.prompt));
		move_cursor_to_coord(&shell->interface, coord->x, coord->y);
		shell->interface.cursor.index = 0;
    }
    else if (rd_flag & RD_CMOVE)
    {
		coord = index_to_coord(&shell->interface.window,
								get_prompt_length(&shell->interface.prompt)
								+ shell->interface.window.point_cursor);
		move_cursor_to_coord(&shell->interface, coord->x, coord->y);
		shell->interface.cursor.index = shell->interface.window.point_cursor;
    }
	free(coord);
}

void    redraw(t_registry *shell)
{

	redraw_line(shell);

	move_cursor(shell);

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
