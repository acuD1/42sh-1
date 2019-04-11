/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:41:22 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/11 18:18:38 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

int8_t	init_cursor(t_interface *itf)
{
	itf->cursor->index = 0;
	itf->cursor->x = get_prompt_len(itf);
	itf->cursor->y = 0;
	return (0);
}
