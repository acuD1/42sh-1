/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_blt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 21:13:30 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

int8_t				setenv_blt(t_registry *shell, char **av)
{
	t_variable		*variable;

	av++;
	if (*av == NULL)
		print_lst(&shell->env);
	else
	{
		variable = (t_variable *)malloc(sizeof(t_variable));
		variable->name = ft_strdup(av[0]);
		variable->data = av[1] ? ft_strdup(av[1]) : ft_strdup("\0");
		add_env(shell, variable->name, variable->data);
	//	if (variable && variable->name && ft_strequ(variable->name, "PATH"))
	//		hash_blt(shell, av);
		clear_node((void **)&variable);
		free(variable);
	}
	return (SUCCESS);
}
