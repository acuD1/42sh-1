/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:36:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 17:57:28 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
/*
t_option			get_option_echo(char *s, char *builtin_name, char *error)
{
	t_option	option;

	option = 0;
	while (*s)
	{
		if (*s == 'n')
			option |= N_OPT;
		else
			return (ERROR_OPT);
		s++;
	}
	return (option);
}*/

int8_t				echo_blt(__unused t_registry *shell, char **av)
{
	t_option	option;

	//if ((option = set_options(++av, get_option_echo)) == ERROR_OPT)
	//	return (FAILURE);
	av++;
	option = 0;
	while (ft_strequ("-n", *av))
	{
		option |= N_OPT;
		av++;
	}
	while (*av)
	{
		ft_putstr(*av++);
		if (*av)
			ft_putchar(' ');
	}
	if (!(option & N_OPT))
		ft_putchar('\n');
	return (SUCCESS);
}
