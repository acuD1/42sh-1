/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_blt_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 18:11:50 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 18:57:05 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static void		ft_process_transform(char *path, char **new_path)
{
	char	*curpath;
	char	*tmp_path;

	if (ft_strequ(path, ".."))
	{
		if ((!ft_strequ(*new_path, "/"))
			&& (tmp_path = ft_strrchr((*new_path) + 1, '/')))
			*tmp_path = '\0';
		else
			*(*new_path + 1) = '\0';
	}
	else
	{
		if ((!ft_strequ(*new_path, "/")))
			curpath = ft_strjoin("/", path);
		else 
			curpath = ft_strdup(path);
		tmp_path = *new_path;
		*new_path = ft_strjoin(tmp_path, curpath);
		ft_strdel(&curpath);
		ft_strdel(&tmp_path);
	}
}

static char		*transform_element_path(char *path, char **new_path)
{
	if (path && !ft_strequ(path, "."))
	{
		ft_process_transform(path, new_path);
		if (access(*new_path, F_OK) != SUCCESS)
		{
			ft_strdel(new_path);
			return (NULL);
		}
	}
	return (*new_path);
}

char			*make_curpath_simple(char *curpath)
{
	char			*new_path;
	char			**tab_path;
	int				i;

	i = 0;
	if (ft_strequ(curpath, "/"))
		return (curpath);
	if (!(tab_path = ft_strsplit(curpath, "/")))
	{
		ft_strdel(&curpath);
		return (NULL);
	}
	new_path = ft_strdup("/");
	ft_strdel(&curpath);
	while (tab_path[i])
	{
		if (!(new_path = transform_element_path(tab_path[i++], &new_path)))
		{
			ft_freetab(&tab_path);
			return (NULL);
		}
	}
	ft_freetab(&tab_path);
	return (new_path);
}
