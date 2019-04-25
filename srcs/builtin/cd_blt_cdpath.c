/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 16:35:32 by ffoissey          #+#    #+#             */
/*   Updated: 2019/04/24 18:13:09 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int		is_valid_path(char *path, char *to_find)
{
	char	*last_slash;

	if (!(last_slash = ft_strrchr(path, '/')))
		return (0);
	return (ft_strequ(last_slash, to_find));

}

static void		ft_delete_end_slash(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	if (path[len - 1] == '/')
		path[len - 1] = '\0';
}

char			*is_cdpath_env(t_registry *shell, char *to_find)
{
	char	*cd_path;
	char	**tab_cd_path;
	int		i;

	i = 0;
	ft_delete_end_slash(to_find);
	if (!(cd_path = get_intern_var(shell, "CDPATH"))
		|| !(tab_cd_path = ft_strsplit(cd_path, ":")))
			return (NULL);
	while (tab_cd_path[i])
	{
		ft_delete_end_slash(tab_cd_path[i]);
		if (is_valid_path(tab_cd_path[i], to_find))
		{
			cd_path = ft_strdup(tab_cd_path[i]);
			ft_freetab(&tab_cd_path);
			return (cd_path);
		}
		i++;
	}
	ft_freetab(&tab_cd_path);
	return (NULL);
}
