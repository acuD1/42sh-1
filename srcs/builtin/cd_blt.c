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

static char			*ft_get_curpath(t_registry *shell, char *path_give_by_user)
{
	char	*home_path;
	char	*curpath;

	if (!path_give_by_user)
	{
		home_path = get_intern_var(shell, "HOME");
		curpath = ft_strdup(home_path ? home_path : get_home_path());	
	}
	else if (ft_strequ(path_give_by_user, "-"))
	{
		if (!(curpath = get_intern_var(shell, "OLDPWD")))
			ft_dprintf(2, CD_ERROR_OLDPWD_NOTSET);
	}
	else if (*path_give_by_user == '/' || *path_give_by_user == '.')
		curpath = ft_strdup(path_give_by_user);
	else
	{
		if (!(curpath = is_cdpath_env(shell, path_give_by_user)))
			curpath = ft_strdup(path_give_by_user);
	}
	return (curpath);
}


static int8_t		process_cd_blt(t_registry *shell, char *path_give_by_user,
					t_option option)
{
	char	*curpath;

	if (!(curpath = ft_get_curpath(shell, path_give_by_user)))
		return (FAILURE);
	if (option & L_OPT)
	{
		if (*curpath != '/')
			if (!(curpath = concat_pwd_with_curpath(shell, &curpath)))
				return (FAILURE);
	}


	ft_printf("Original String: %s\nCD String:       %s\n", path_give_by_user, curpath);
	return (SUCCESS);
}


int8_t				cd_blt(t_registry *shell, char **av)
{
	t_option	option;

	av++;
	if ((option = set_options(&av, get_option_cd)) == ERROR_OPT)
		return (FAILURE_OPTION);
	return (process_cd_blt(shell, *av, option));
}
/*
get_intern_var(shell, "");
add_intern_var(shell, "");
*/
