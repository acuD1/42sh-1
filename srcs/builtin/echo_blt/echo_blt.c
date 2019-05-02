/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_blt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:57 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 18:51:43 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

//////__unused shell
int8_t				echo_blt(t_registry *shell, char **av)
{
	t_option	option;

///// delete (void)shell
	(void)shell;
	++av;
	option = 0;
	while (ft_strequ("-n", *av) == TRUE)
	{
		option |= N_OPT;
		++av;
	}
	while (*av != NULL)
	{
		ft_putstr(*av);
		++av;
		if (*av != NULL)
			ft_putchar(' ');
	}
	if ((option & N_OPT) == FALSE)
		ft_putchar('\n');
	return (SUCCESS);
}
