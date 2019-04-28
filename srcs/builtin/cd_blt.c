/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/26 17:29:45 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static char			*ft_get_curpath(t_registry *shell, char *path_give_by_user)
{
	char	*home_path;
	char	*curpath;

	if (path_give_by_user == NULL)
	{
		home_path = get_env_var(shell, "HOME");
		curpath = ft_strdup(home_path != NULL ? home_path : get_home_path());
	}
	else if (ft_strequ(path_give_by_user, "-") == TRUE)
	{
		if ((curpath = get_env_var(shell, "OLDPWD")) != NULL)
			ft_dprintf(2, CD_ERROR_OLDPWD_NOTSET);
		else
			curpath = ft_strdup(curpath);
	}
	else if (*path_give_by_user == '/' || *path_give_by_user == '.')
		curpath = ft_strdup(path_give_by_user);
	else
	{
		if ((curpath = is_cdpath_env(shell, path_give_by_user)) != NULL)
			curpath = ft_strdup(path_give_by_user);
	}
	return (curpath);
}

static int8_t		change_directory(t_registry *shell, char *curpath,
					char *path_give_by_user, t_option option)
{
	char		*pwd;
	struct stat	stat;

	if ((pwd = get_env_var(shell, "PWD")) != NULL)
		pwd = getcwd(pwd, PATH_MAX);
	if (access(curpath, F_OK) != SUCCESS)
		ft_dprintf(2, "cd: no such file or directory: %s\n", path_give_by_user);
	else if (lstat(curpath, &stat) == FAILURE)
		ft_dprintf(2, "cd: not a directory: %s\n", path_give_by_user);
	else if (access(curpath, R_OK) != SUCCESS)
		ft_dprintf(2, "21sh: cd: %s: Permission denied\n", path_give_by_user);
	else if (chdir(curpath) == FAILURE)
		ft_dprintf(2, "chdir() failed\n");
	else
	{
		add_env(shell, "OLDPWD", ft_strdup(pwd));
		add_env(shell, "PWD",
				ft_strdup(option & P_OPT ? getcwd(pwd, PATH_MAX) : curpath));
		ft_strdel(&curpath);
		if (ft_strequ(path_give_by_user, "-") == TRUE)
			ft_printf("%s\n", get_env_var(shell, "PWD"));
		return (SUCCESS);
	}
	ft_strdel(&curpath);
	return (FAILURE);
}

static int8_t		is_root_path(char *path)
{
	int		i;

	i = 0;
	if (path == NULL || path[0] == '\0')
		return (FALSE);
	while (path[i] != '\0')
	{
		if (path[i] != '/')
			return (FALSE);
		i++;
	}
	path[1] = '\0';
	return (TRUE);
}

int8_t				cd_blt(t_registry *shell, char **av)
{
	char		*curpath;
	t_option	option;

	av++;
	if (((option = set_options(&av, get_option_cd)) == ERROR_OPT)
		|| (curpath = ft_get_curpath(shell, *av)) == NULL)
		return (FAILURE);
	if (is_root_path(curpath) == FALSE
		&& curpath[ft_strlen(curpath) - 1] == '/')
		curpath[ft_strlen(curpath) - 1] = '\0';
	if ((option & P_OPT) == FALSE)
	{
		if (*curpath != '/')
			if ((curpath = concat_pwd_with_curpath(shell, &curpath)) == NULL)
				return (FAILURE);
		if ((curpath = make_curpath_simple(curpath)) == NULL)
		{
			ft_dprintf(2, "21sh: cd: %s: No such file or directory\n", *av);
			return (FAILURE);
		}
		else if (ft_strlen(curpath) + 1 >= PATH_MAX)
			curpath = get_relative_path(&curpath);
	}
	return (change_directory(shell, curpath, *av, option));
}
