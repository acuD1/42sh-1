/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 18:57:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_option			get_option_cd(char *s, t_option option)
{
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


static int8_t		process_cd_blt(t_registry *shell, char *path_give_by_user,
					t_option option)
{
	char	*home_path;
	char	*curpath;
	char	*cdpath_env;

	(void)option;
	home_path = get_intern_var(shell, "HOME");
	if (!path_give_by_user)
	{
		if (!home_path)
			curpath = NULL;
			////// get home_path by another way
		curpath = ft_strdup(home_path);	
	}
	else if (*path_give_by_user == '/')
		curpath = ft_strdup(path_give_by_user);
	else if (*path_give_by_user == '.')
	{
		/// GO_TO_6_STEP
	}
	else if ((cdpath_env = is_cdpath_env(shell, path_give_by_user)))
		curpath = cdpath_env;
	return (SUCCESS);
}


int8_t				cd_blt(t_registry *shell, char **av)
{
	t_option	option;

	av++;
	if ((option = set_options(&av, get_option_cd)) == ERROR_OPT)
		return (FAILURE_OPTION);
	process_cd_blt(shell, *av, option);
	return (SUCCESS);
}
/*
get_intern_var(shell, "");
add_intern_var(shell, "");
*/
