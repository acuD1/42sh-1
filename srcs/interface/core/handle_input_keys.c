/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_keys.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 14:40:53 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:46:52 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "log.h"

static void			handle_printable_char(char c, t_registry *shell)
{
	t_interface *itf;

	itf = shell->interface;
	if (validate_interface_content(itf) != 0)
		return ;
	if ((uint32_t)ft_vctlen(itf->line) >= itf->window->max_chars)
		return ;
	if (itf->cursor->index > (itf->line->size - 2))
		ft_vctrescale(itf->line);
	if (itf->cursor->index != ft_vctlen(itf->line))
	{
		shift_content_right_once(itf->line, itf->cursor->index);
		itf->line->buffer[itf->cursor->index] = c;
	}
	else
		itf->line->buffer[ft_vctlen(itf->line)] = c;
	itf->cursor->index = redraw_after_cursor(shell);
	tc_ak_arrow_right(shell);
}

void				handle_input_key(char c[READ_SIZE], t_registry *shell)
{
	uint32_t		index;
	unsigned long	value;

	if (is_printable(c))
		handle_printable_char(c[0], shell);
	else
	{
		index = 0;
		value = compute_mask(c);
		while (index < AK_AMOUNT)
		{
			if (value == shell->interface->ak_masks[index])
				(shell->interface->tc_call)[index](shell);
			++index;
		}
	}
}
