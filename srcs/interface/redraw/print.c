/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 10:49:05 by skuppers          #+#    #+#             */
/*   Updated: 2019/04/30 20:11:29 by ffoissey         ###   ########.fr       */
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
	uint8_t		color;
	char		*color_str_start;
	char		*color_str_end;

	i = 0;
	color = 0;
	color_str_start = PS1_COLOR_START;
	color_str_end = PS1_COLOR_END;
	if (ft_strequ(str, INT_PS1_VALUE) == FALSE
		|| ft_strequ(str, INT_PS2_VALUE) == FALSE
		|| ft_strequ(str, INT_PS3_VALUE) == FALSE
		|| ft_strequ(str, INT_PS4_VALUE) == FALSE)
		color = 1;
	while (color == 1 && *color_str_start != '\0')
		print_char(itf, *color_str_start++);
	while (i < ft_strlen(str))
		print_char(itf, str[i++]);
	while (color == 1 && *color_str_end != '\0')
		print_char(itf, *color_str_end++);
}
