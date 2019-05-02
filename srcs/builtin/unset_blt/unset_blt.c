/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_blt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/30 17:40:18 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "interface_functions.h"

static void			reset_prompt(t_registry *shell, char **av)
{
	if (ft_strequ(*av, "*") == TRUE)
		fill_interface_related_internals(shell);
	else if (ft_strequ(*av, "PS1") == TRUE)
		get_prompt_ps1(shell);
	else if (ft_strequ(*av, "PS2") == TRUE)
		add_internal(shell, INT_PS2, INT_PS2_VALUE);
	else if (ft_strequ(*av, "PS3") == TRUE)
		add_internal(shell, INT_PS3, INT_PS3_VALUE);
	else if (ft_strequ(*av, "PS4") == TRUE)
		add_internal(shell, INT_PS4, INT_PS4_VALUE);
}
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
	reset_prompt(shell, av);
	return (SUCCESS);
}
