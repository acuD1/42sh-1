/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_blt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 17:32:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int8_t				unsetenv_blt(t_registry *shell, char **av)
{
	av++;
	if (*av == NULL)
	{	
		ft_dprintf(2, UNSETENV_USAGE);
		return (FAILURE);
	}
	if (ft_strequ(*av, "*") == TRUE)
		free_lst(&shell->env);
	else if (shell->env != NULL)
		free_node(&shell->env, *av);
	if (ft_strequ(*av, "PATH") == TRUE
		|| ft_strequ(*av, "*") == TRUE)
		hash_blt(shell, NULL);
	return (SUCCESS);
}
