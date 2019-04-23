/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:27:08 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/23 21:30:18 by cempassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <unistd.h>

static void	hash_bin(t_registry *shell, char *path)
{
	DIR				*dip;
	char			*asp;
	struct dirent	*dit;

	if ((dip = opendir(path)) != NULL)
	{
		while ((dit = readdir(dip)) != NULL)
		{
			asp = NULL;
			if (dit->d_name[0] == '.')
				continue;
			ft_asprintf(&asp, "%s/%s", path, dit->d_name);
			if (asp)
			{
				if (!ft_hmap_insert(&(shell->bin_hashmap), dit->d_name, asp))
					free(asp);
			}
		}
		if (!closedir(dip))
			return ;
	}
}

static void	hash_builtin(t_registry *shell)
{
	if (!ft_hmap_insert(&(shell->blt_hashmap), "echo", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : echo built-in\n");
	if (!ft_hmap_insert(&(shell->blt_hashmap), "cd", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : cd built-in\n");
	if (!ft_hmap_insert(&(shell->blt_hashmap), "setenv", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : setenv built-in\n");
	if (!ft_hmap_insert(&(shell->blt_hashmap), "unsetenv", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : unsetenv built-in\n");
	if (!ft_hmap_insert(&(shell->blt_hashmap), "env", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : env built-in\n");
	if (!ft_hmap_insert(&(shell->blt_hashmap), "hash", hash_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : hash built-in\n");
	if (!ft_hmap_insert(&(shell->blt_hashmap), "exit", exit_blt))
		ft_dprintf(2, "[ERROR] Hmap insert failure : exit built-in\n");
}

int			hash_blt(t_registry *shell)
{
	int				i;
	char			**tabs;

	i = 0;
	if (shell->bin_hashmap.used > 0)
		ft_hmap_free_content(&(shell->bin_hashmap), free);
	tabs = ft_strsplit(get_data(shell->env, "PATH"), ":");
	if (!tabs)
		return (0);
	while (tabs[i])
		hash_bin(shell, tabs[i++]);
	hash_builtin(shell);
	ft_freetab(&tabs);
	return (1);
}
