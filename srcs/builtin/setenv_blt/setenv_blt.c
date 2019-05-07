/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_blt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/07 15:03:04 by nrechati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include "builtin.h"

int8_t				setenv_blt(t_registry *shell, char **av)
{
	t_variable		*variable;

	++av;
	if (*av == NULL)
		print_lst(&shell->env, shell->cur_fd.err);
	else
	{
		variable = (t_variable *)ft_malloc(sizeof(t_variable));
		if (variable == NULL)
			return (FAILURE);
		variable->name = ft_strdup(av[0]);
		variable->data = av[1] ? ft_strdup(av[1]) : ft_strdup("\0");
		add_env(shell, variable->name, variable->data);
		if (variable && variable->name && ft_strequ(variable->name, "PATH"))
			hash_blt(shell, av);
		clear_node((void **)&variable);
		ft_free(variable);
	}
	return (SUCCESS);
}
