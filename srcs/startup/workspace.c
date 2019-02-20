/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   workspace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuppers <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:31:41 by skuppers          #+#    #+#             */
/*   Updated: 2019/02/20 15:12:14 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "startup.h"

static inline int		directory_exist(char *path)
{
	return (access(path, F_OK));
}

static inline int		directory_got_permissions(char *path)
{
	return (access(path, R_OK | W_OK | X_OK));
}

static inline DIR		*get_directory(char *path)
{
	DIR	*dir;

	if ((dir = opendir(directory)) != NULL)
		return (dir);
	return (NULL);
}

char		*search_home_directory(t_registry *reg);
{
	return (get_env_node_value(reg->environment, ENV_HOME_NAME));
}

unsigned int		init_workspace(t_registry *registry)
{
	char	*home_path;
	char	*workspace_path;
	char	*tmp;

	registry->home_path = search_home_directory(registry);
	if (registry->home_path != NULL)
	{
		tmp = ft_strjoin(registry->home_path, "/");
		registry->workspace_path = ft_strjoinfree(tmp, WORKSPACE_NAME, 1);
	}
	else
	{
		//handle no homepath
		return (1);
	}

	if (directory_exist(registry->workspace_path))
	{
		if (directory_got_permissions(registry->workspace_path))
		{
			// check for sub-directories existance and perms
		}
		else
		{
			// return 1 | no permissions
		}
	}
	else
	{
		if (directory_got_permissions(registry->home_path))
		{
			//create WORKSPACE directory
			// and subdirectories
			// with corresponding files
		}
		else
		{
			// return 1, no permissions
			// if no permission, force live debug
		}
	}
	return (0);
}
