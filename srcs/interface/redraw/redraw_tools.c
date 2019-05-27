/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 09:48:40 by skuppers          #+#    #+#             */
/*   Updated: 2019/05/27 13:32:36 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "interface_functions.h"

t_coord		*index_to_coord(t_window *win, uint64_t index)
{
	t_coord	*co;

	//TODO: change global
//	ft_dprintf(3, "Index is :%d\n", index);
	if (index > vct_len(g_shell->interface.line)
				+ get_prompt_length(&g_shell->interface.prompt) + 1)
		index = vct_len(g_shell->interface.line)
				+ get_prompt_length(&g_shell->interface.prompt);

	if (win->cols == 0)
		return (NULL);
	if (!(co = malloc(sizeof(t_coord))))
		return (NULL);
//	ft_dprintf(3, "Malloc ok\n");

	co->x = (index % win->cols);
	co->y = (index / win->cols);
	return (co);
}

void		print_char(t_interface *itf, char c)
{
	write(1, &c, 1);
	itf->cursor.x++;
	if (itf->cursor.x == itf->window.cols)
	{
		itf->cursor.y++;
		itf->cursor.x = 0;
	}
	itf->cursor.index++;
}


void		print_loop(t_interface *itf, char *str)
{
	while (*str != '\0')
	{
		write(1, str, 1);
		++str;
		itf->cursor.x++;
		if (itf->cursor.x == itf->window.cols)
		{
			itf->cursor.y++;
			itf->cursor.x = 0;
		}
		itf->cursor.index++;
	}
}

void	print_to_window(t_interface *itf, t_vector *text)
{
	char *str;

	str = vct_get_string(text);
	while (*str != '\0')
	{
		write(1, str, 1);
		++str;
		itf->cursor.x++;
		if (itf->cursor.x == itf->window.cols)
		{
			itf->cursor.y++;
			itf->cursor.x = 0;
		}
	}

//	if (vct_len(text) < itf->window.max_chars)
//		write(1, vct_get_string(text), vct_len(text));
//	else if (itf->window.max_chars > 1)
//		write(1, "> ", 2);
}

