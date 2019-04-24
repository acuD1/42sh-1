/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 18:37:45 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_option			get_option_cd(char *s)
{
	t_option	option;

	option = 0;
	while (*s)
	{
		if (*s == 'L')
			option |= L_OPT;
		else if (*s == 'P')
			option |= P_OPT;
		else
		{
			ft_dprintf(2, "21sh: cd: -%c: invalid option\n");
			ft_dprintf(2, CD_USAGE);
			return (ERROR_OPT);
		}
		s++;
	}
	return (option);
}




static int8_t		process_cd(t_registry *shell, char **av)
{

}


int8_t				cd_blt(t_registry *shell, char **av)
{
	t_option	option;
	char		**tab;
	
	av++;
	if ((option = set_options(&av, get_option_cd)) == ERROR_OPT)
		return (FAILURE);
	if (!*av)
		// go to $HOME
	else if (ft_strequ(*av, "-"))
	{
		// go to $OLDPWD
	}
	else if (**av == '/')
		// Absolute path
	else
	{
		// Get $PWD and concat with relative path (Warning : end by '/')
		// Relative path
	}
	return (SUCCESS);
}

get_intern_var(shell, "");
add_intern_var(shell, "");

