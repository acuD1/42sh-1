/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_blt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 15:23:09 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 14:03:39 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "21sh.h"

int8_t				set_blt(t_registry *shell, char **av)
{
	(void)av;
	print_lst(&shell->intern);
	return (SUCCESS);
}
