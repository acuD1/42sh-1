/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_special_ak.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:06:28 by skuppers          #+#    #+#             */
/*   Updated: 2019/01/07 12:00:03 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_edit.h"

int		ak_keycodes[AK_AMOUNT][READ_SIZE];

void	init_ak_home(void)
{
	ak_keycodes[AK_HOME][0] = 27;
	ak_keycodes[AK_HOME][1] = 91;
	ak_keycodes[AK_HOME][2] = 72;
}

void	init_ak_end(void)
{
	ak_keycodes[AK_END][0] = 27;
	ak_keycodes[AK_END][1] = 91;
	ak_keycodes[AK_END][2] = 70;
}

void	init_ak_backspace(void)
{
	ak_keycodes[AK_BACKSPACE][0] = 127;
}

void	init_ak_delete(void)
{
	ak_keycodes[AK_DELETE][0] = 27;
	ak_keycodes[AK_DELETE][1] = 91;
	ak_keycodes[AK_DELETE][2] = 51;
	ak_keycodes[AK_DELETE][3] = 126;
}

void	init_ak_enter(void)
{
	ak_keycodes[AK_ENTER][0] = 10;
}
