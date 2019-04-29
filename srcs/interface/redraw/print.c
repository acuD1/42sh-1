/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:49:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/27 15:53:15 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "interface_functions.h"

void	print_char(t_interface *itf, char d)
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

void	print_words(t_interface *itf, char *str)
{
	uint32_t	i;

	i = 0;
	while (i < ft_strlen(str))
		print_char(itf, str[i++]);
}
