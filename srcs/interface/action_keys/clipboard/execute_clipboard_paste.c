/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_clipboard_ak.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 10:45:51 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/09 19:16:10 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"
#include "ft_printf.h"

static int	compare_len(t_vector *a, t_vector *b, size_t max)
{
	if (ft_vctlen(a) + ft_vctlen(b) >= max)
		return (1);
	return (0);
}

int	insert_clipboard(t_interface_registry *itf)
{
	int				length;
	char			*after;
	char			*before;
	char			*concat;

	length = 0;
	concat = NULL;
	before = NULL;
	after = NULL;
	before = ft_strsub(itf->line->buffer,
				0, itf->window->cursor);
	after = ft_strsub(itf->line->buffer,
			itf->window->cursor, ft_vctlen(itf->line));
	ft_asprintf(&concat, "%s%s%s",
			before, itf->clip->buffer, after);
	ft_bzero(itf->line->buffer, itf->line->size);
	ft_strncpy(itf->line->buffer, concat, ft_strlen(concat));
	length = ft_strlen(before) + ft_strlen(itf->clip->buffer);
	ft_strdel(&concat);
	ft_strdel(&after);
	ft_strdel(&before);
	return (length);
}

void	append_clipboard(t_interface_registry *itf)
{
	itf->line->buffer = ft_strcat(itf->line->buffer,
			itf->clip->buffer);
	redraw_after_cursor(itf);
	tc_ak_end(itf);
}

int		tc_ak_paste_clipboard(t_interface_registry *itf)
{
	size_t			go_front;

	if (validate_interface_content(itf) != 0)
		return (-1);
	if (compare_len(itf->line, itf->clip,
				(size_t)itf->window->max_line_len) != 0)
		return (-1);
	while (itf->line->size < (ft_vctlen(itf->line)
				+ ft_vctlen(itf->clip) + 2))
		ft_vctrescale(itf->line);

	if (itf->line->buffer[itf->window->cursor] != '\0')
	{
		go_front = insert_clipboard(itf);
		tc_ak_home(itf);
		redraw_after_cursor(itf);
		while (go_front-- > 0)
			tc_ak_arrow_right(itf);
	}
	else
		append_clipboard(itf);
	return (0);
}
