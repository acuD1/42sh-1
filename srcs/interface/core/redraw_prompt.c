/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 09:08:59 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/08 11:00:33 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"
#include "log.h"
#include "libft.h"


static void print_char(char d, t_winsize *ws)
{
	if (ws->x == ws->cols)
	{
		tputs(g_termcaps->cs_down, 1, &ft_putc);
		ws->x = 0;
		ws->y++;
	}
	write(1, &d, 1);
	ws->cursor_index++;
	ws->x++;
}

void	print_words(char *str, t_winsize *ws)
{
	int i;

	i = 0;
	while (i < (int)ft_strlen(str))
		print_char(str[i++], ws);
}

int		redraw_input_line(t_vector *vector, t_winsize *ws)
{
	int i;
	int	initial_cursor_index;

	i = 0;
	initial_cursor_index = ws->cursor_index;
	ws->cursor_index = tc_ak_home(vector, ws);
	while (i++ < (int)vector->size + 2)
		print_char(' ', ws);
	ws->cursor_index = tc_ak_home(vector, ws);
	i = 0;
	while (i < (int)ft_vctlen(vector))
		print_char(vector->buffer[i++], ws);
	ws->cursor_index = tc_ak_home(vector, ws);
	i = 0;
while (i < initial_cursor_index && i++ < (int)ft_vctlen(vector))
		ws->cursor_index = tc_ak_arrow_right(vector, ws);
	return (ws->cursor_index);
}
