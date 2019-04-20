/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:49:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/20 04:25:08 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"
#include "line_edit.h"

void	print_char(char d, t_interface *itf)
{
	write(1, &d, 1);
	itf->cursor.index++;
	itf->cursor.x++;
	if (itf->cursor.x == itf->window.cols)
	{
		tputs(itf->termcaps.cs_down, 1, &ft_putc);
		itf->cursor.x = 0;
		itf->cursor.y++;
	}
}

void	print_words(char *str, t_interface *itf)
{
	uint32_t	i;

	i = 0;
	while (i < ft_strlen(str))
		print_char(str[i++], itf);
}
