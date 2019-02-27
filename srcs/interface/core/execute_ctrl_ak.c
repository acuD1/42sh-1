/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ctrl_ak.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 07:30:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/27 15:36:43 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

t_vector	*g_clipboard;

//TODO: HANDLE TABULATIONS
int		tc_ak_next_word(t_interface_registry *itf_reg)
{
	if (itf_reg->window->cursor_index == (int)ft_vctlen(itf_reg->vector))
		return (itf_reg->window->cursor_index);
	else
	{
		while (itf_reg->window->cursor_index < (int)ft_vctlen(itf_reg->vector)
				&& itf_reg->vector->buffer[itf_reg->window->cursor_index] != ' ')
			itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
		while (itf_reg->window->cursor_index < (int)ft_vctlen(itf_reg->vector)
				&& (itf_reg->vector->buffer[itf_reg->window->cursor_index] == ' '))
			itf_reg->window->cursor_index = tc_ak_arrow_right(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}

int		tc_ak_prev_word(t_interface_registry *itf_reg)
{
	if (itf_reg->window->cursor_index == 0)
		return (0);
	else
	{
		while (itf_reg->window->cursor_index > 0
				&& itf_reg->vector->buffer[itf_reg->window->cursor_index] != ' ')
			itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
		while (itf_reg->window->cursor_index > 0
				&& (itf_reg->vector->buffer[itf_reg->window->cursor_index] == ' '))
			itf_reg->window->cursor_index = tc_ak_arrow_left(itf_reg);
	}
	return (itf_reg->window->cursor_index);
}

static int cut_vector(t_vector *vect, t_winsize *ws, int before)
{
	char	*tmp;
	char	*foobar;

	tmp = ft_strnew(vect->size);
	if (before > 0)
	{
		foobar = ft_strsub(vect->buffer, ws->cursor_index, ft_vctlen(vect));
		tmp = ft_strcpy(tmp, foobar);
		ft_strdel(&foobar);
	}
	else
		tmp = ft_strncpy(tmp, vect->buffer, ws->cursor_index);
	ft_strdel(&(vect->buffer));
	vect->buffer = tmp;
	return (0);
}

int		tc_ak_cut_before_cursor(t_interface_registry *itf_reg)
{
	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < itf_reg->vector->size)
		ft_vctrescale(g_clipboard);
	g_clipboard->buffer = ft_strncpy(g_clipboard->buffer, itf_reg->vector->buffer, itf_reg->window->cursor_index);
	cut_vector(itf_reg->vector, itf_reg->window, 1);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_cut_after_cursor(t_interface_registry *itf_reg)
{
	char *tmp;

	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < itf_reg->vector->size)
		ft_vctrescale(g_clipboard);
	tmp = ft_strsub(itf_reg->vector->buffer, itf_reg->window->cursor_index, ft_vctlen(itf_reg->vector));
	g_clipboard->buffer = ft_strcpy(g_clipboard->buffer, tmp);
	ft_strdel(&tmp);
	cut_vector(itf_reg->vector, itf_reg->window, -1);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_cut_line(t_interface_registry *itf_reg)
{
	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < itf_reg->vector->size)
		ft_vctrescale(g_clipboard);
	g_clipboard->buffer = ft_strcpy(g_clipboard->buffer, itf_reg->vector->buffer);
	ft_bzero(itf_reg->vector->buffer, itf_reg->vector->size);
	redraw_input_line(itf_reg);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_copy_before_cursor(t_interface_registry *itf_reg)
{
	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < itf_reg->vector->size)
		ft_vctrescale(g_clipboard);
	g_clipboard->buffer = ft_strncpy(g_clipboard->buffer, itf_reg->vector->buffer, itf_reg->window->cursor_index);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_copy_after_cursor(t_interface_registry *itf_reg)
{
	char	*tmp;

	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < itf_reg->vector->size)
		ft_vctrescale(g_clipboard);
	tmp = ft_strsub(itf_reg->vector->buffer, itf_reg->window->cursor_index, ft_vctlen(itf_reg->vector));
	g_clipboard->buffer = ft_strcpy(g_clipboard->buffer, tmp);
	ft_strdel(&tmp);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_copy_line(t_interface_registry *itf_reg)
{
	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < itf_reg->vector->size)
		ft_vctrescale(g_clipboard);
	g_clipboard->buffer = ft_strcpy(g_clipboard->buffer, itf_reg->vector->buffer);
	return (itf_reg->window->cursor_index);
}

int		tc_ak_paste_clipboard(t_interface_registry *itf_reg)
{
	char			*after;
	char			*before;

	if (itf_reg->vector->size <
			(ft_vctlen(itf_reg->vector) + ft_vctlen(g_clipboard) + 1))
		ft_vctrescale(itf_reg->vector);
	//TODO: problem
	if (itf_reg->vector->buffer[itf_reg->window->cursor_index] != '\0')
	{
		before = ft_strsub(itf_reg->vector->buffer, 0, itf_reg->window->cursor_index);
		after = ft_strsub(itf_reg->vector->buffer, itf_reg->window->cursor_index, ft_vctlen(itf_reg->vector));
		ft_bzero(itf_reg->vector->buffer, itf_reg->vector->size);
		itf_reg->vector->buffer = ft_strcpy(itf_reg->vector->buffer, before);
		itf_reg->vector->buffer = ft_strcat(itf_reg->vector->buffer, g_clipboard->buffer);
		itf_reg->vector->buffer = ft_strcat(itf_reg->vector->buffer, after);
		redraw_input_line(itf_reg);
		ft_strdel(&after);
		ft_strdel(&before);
	}
	else
	{
		ft_printf_fd(2, "Pasting : %s\n", g_clipboard->buffer);
		print_words(g_clipboard->buffer, itf_reg);
		itf_reg->vector->buffer = ft_strcat(itf_reg->vector->buffer, g_clipboard->buffer);
	}
	return (ft_vctlen(itf_reg->vector));
}

int		tc_ak_clear_screen(t_interface_registry *itf_reg)
{
	(void)itf_reg;
	return (itf_reg->window->cursor_index);
}
