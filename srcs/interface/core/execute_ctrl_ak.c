/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ctrl_ak.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 07:30:12 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/08 11:39:45 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

t_vector	*g_clipboard;

//TODO: HANDLE TABULATIONS
int		tc_ak_next_word(t_vector *vector, t_winsize *ws)
{
	if (ws->cursor_index == (int)ft_vctlen(vector))
		return (ws->cursor_index);
	else
	{
		while (ws->cursor_index < (int)ft_vctlen(vector) && vector->buffer[ws->cursor_index] != ' ')
			ws->cursor_index = tc_ak_arrow_right(vector, ws);
		while (ws->cursor_index < (int)ft_vctlen(vector) && (vector->buffer[ws->cursor_index] == ' '))
			ws->cursor_index = tc_ak_arrow_right(vector, ws);
	}
	return (ws->cursor_index);
}

int		tc_ak_prev_word(t_vector *vector, t_winsize *ws)
{
	if (ws->cursor_index == 0)
		return (0);
	else
	{
		while (ws->cursor_index > 0 && vector->buffer[ws->cursor_index] != ' ')
			ws->cursor_index = tc_ak_arrow_left(vector, ws);
		while (ws->cursor_index > 0 && (vector->buffer[ws->cursor_index] == ' '))
			ws->cursor_index = tc_ak_arrow_left(vector, ws);
	}
	return (ws->cursor_index);
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

int		tc_ak_cut_before_cursor(t_vector *vector, t_winsize *ws)
{
	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < vector->size)
		ft_vctrescale(g_clipboard);
	g_clipboard->buffer = ft_strncpy(g_clipboard->buffer, vector->buffer, ws->cursor_index);
	cut_vector(vector, ws, 1);
	redraw_input_line(vector, ws);
	return (ws->cursor_index);
}

int		tc_ak_cut_after_cursor(t_vector *vector, t_winsize *ws)
{
	char *tmp;

	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < vector->size)
		ft_vctrescale(g_clipboard);
	tmp = ft_strsub(vector->buffer, ws->cursor_index, ft_vctlen(vector));
	g_clipboard->buffer = ft_strcpy(g_clipboard->buffer, tmp);
	ft_strdel(&tmp);
	cut_vector(vector, ws, -1);
	redraw_input_line(vector, ws);
	return (ws->cursor_index);
}

int		tc_ak_cut_line(t_vector *vector, t_winsize *ws)
{
	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < vector->size)
		ft_vctrescale(g_clipboard);
	g_clipboard->buffer = ft_strcpy(g_clipboard->buffer, vector->buffer);
	ft_bzero(vector->buffer, vector->size);
	redraw_input_line(vector, ws);
	return (ws->cursor_index);
}

int		tc_ak_copy_before_cursor(t_vector *vector, t_winsize *ws)
{
	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < vector->size)
		ft_vctrescale(g_clipboard);
	g_clipboard->buffer = ft_strncpy(g_clipboard->buffer, vector->buffer, ws->cursor_index);
	return (ws->cursor_index);
}

int		tc_ak_copy_after_cursor(t_vector *vector, t_winsize *ws)
{
	char	*tmp;

	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < vector->size)
		ft_vctrescale(g_clipboard);
	tmp = ft_strsub(vector->buffer, ws->cursor_index, ft_vctlen(vector));
	g_clipboard->buffer = ft_strcpy(g_clipboard->buffer, tmp);
	ft_strdel(&tmp);
	return (ws->cursor_index);
}

int		tc_ak_copy_line(t_vector *vector, t_winsize *ws)
{
	ft_bzero(g_clipboard->buffer, g_clipboard->size);
	while (g_clipboard->size < vector->size)
		ft_vctrescale(g_clipboard);
	g_clipboard->buffer = ft_strcpy(g_clipboard->buffer, vector->buffer);
	return (ws->cursor_index);
}

int		tc_ak_paste_clipboard(t_vector *vector, t_winsize *ws)
{
	char			*after;
	char			*before;

	if (vector->size < (ft_vctlen(vector) + ft_vctlen(g_clipboard) + 1))
		ft_vctrescale(vector);
	if (vector->buffer[ws->cursor_index] != '\0')
	{
		before = ft_strsub(vector->buffer, 0, ws->cursor_index);
		after = ft_strsub(vector->buffer, ws->cursor_index, ft_vctlen(vector));
		ft_bzero(vector->buffer, vector->size);
		vector->buffer = ft_strcpy(vector->buffer, before);
		vector->buffer = ft_strcat(vector->buffer, g_clipboard->buffer);
		vector->buffer = ft_strcat(vector->buffer, after);
		redraw_input_line(vector, ws);
		ft_strdel(&after);
		ft_strdel(&before);
	}
	else
	{
		ft_printf_fd(2, "Pasting : %s\n", g_clipboard->buffer);
		print_words(g_clipboard->buffer, ws);
		vector->buffer = ft_strcat(vector->buffer, g_clipboard->buffer);
	}
	return (ft_vctlen(vector));
}

int		tc_ak_clear_screen(t_vector *vector, t_winsize *ws)
{
	(void)vector;
	return (ws->cursor_index);
}
