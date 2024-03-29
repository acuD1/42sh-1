/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt_cdpath.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <skuppers@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:35:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/05/07 15:03:04 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "sh21.h"

static char		*is_valid_path(char *path, const char *to_find)
{
	char	*complete_path;

	if ((complete_path = ft_strjoin(path, to_find)) == NULL)
		return (NULL);
	if (access(complete_path, F_OK) == SUCCESS)
		return (complete_path);
	ft_strdel(&complete_path);
	return (NULL);
}

static uint8_t	add_end_slash(char **path)
{
	size_t	len;
	char	*tmp_path;

	tmp_path = *path;
	len = ft_strlen(tmp_path);
	if (len == 0)
		return (TRUE);
	if (tmp_path[len - 1] != '/')
	{
		tmp_path = *path;
		if ((*path = ft_strjoin(*path, "/")) == NULL)
			return (FALSE);
		ft_strdel(&tmp_path);
	}
	return (TRUE);
}

char			*is_cdpath_env(t_registry *shell, const char *to_find)
{
	char		*cd_path;
	char		**tab_cd_path;
	uint32_t	i;

	i = 0;
	if ((cd_path = get_env_var(shell, "CDPATH")) == NULL)
		return (is_valid_path("./", to_find));
	if ((tab_cd_path = ft_strsplit(cd_path, ":")) == NULL)
		return (NULL);
	while (tab_cd_path[i] != NULL)
	{
		if (add_end_slash(tab_cd_path + i) == FALSE)
		{
			ft_freetab(&tab_cd_path);
			return (NULL);
		}
		if ((cd_path = is_valid_path(tab_cd_path[i], to_find)) != NULL)
		{
			ft_freetab(&tab_cd_path);
			return (cd_path);
		}
		i++;
	}
	ft_freetab(&tab_cd_path);
	return (NULL);
}

uint8_t			check_path(t_registry *shell, char *curpath,
						const char *path_give_by_user)
{
	char		*oldpwd;
	struct stat	stat;

	if (ft_strequ(path_give_by_user, "-") == TRUE)
	{
		oldpwd = get_env_var(shell, "OLDPWD");
		if (oldpwd != NULL)
			path_give_by_user = oldpwd;
	}
	if (access(curpath, F_OK) != SUCCESS)
		ft_dprintf(shell->cur_fd.err,
					"cd: no such file or directory: %s\n", path_give_by_user);
	else if (lstat(curpath, &stat) == FAILURE)
		ft_dprintf(shell->cur_fd.err,
					"cd: not a directory: %s\n", path_give_by_user);
	else if (access(curpath, R_OK) != SUCCESS)
		ft_dprintf(shell->cur_fd.err,
					"21sh: cd: %s: Permission denied\n", path_give_by_user);
	else if (chdir(curpath) == FAILURE)
		ft_dprintf(shell->cur_fd.err, "chdir() failed\n");
	else
		return (TRUE);
	return (FALSE);
}
