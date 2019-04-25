/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_blt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 18:57:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int8_t				setenv_blt(t_registry *shell, char **av)
{
	t_node		*node;

	av++;
	if (!*av)
		print_lst(&shell->env);
	else
	{
		node = (t_node *)malloc(sizeof(t_node));
		node->var = ft_strdup(av[0]);
		node->data = av[1] ? ft_strdup(av[1]) : ft_strdup("\0");
		add_env(shell, node->var, node->data);
	}
	return (SUCCESS);
}