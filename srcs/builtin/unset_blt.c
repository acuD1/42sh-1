/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_blt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 17:32:17 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "interface_functions.h"

int8_t				unset_blt(t_registry *shell, char **av)
{
	av++;
	if (*av == NULL)
	{	
		ft_dprintf(2, UNSET_USAGE);
		return (FAILURE);
	}
	if (ft_strequ(*av, "*") == TRUE)
		free_lst(&shell->intern);
	else if (shell->env != NULL)
		free_node(&shell->intern, *av);
	if (ft_strnequ(*av, "PS", 2) == TRUE || ft_strequ(*av, "*") == TRUE)
		fill_interface_related_internals(shell);
	return (SUCCESS);
}
