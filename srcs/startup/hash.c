/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrechati <nrechati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 15:27:08 by nrechati          #+#    #+#             */
/*   Updated: 2019/04/26 16:37:26 by skuppers         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include <unistd.h>
#include "builtin.h"

static void	hash_bin(t_registry *reg, char *bin)
{
	char			*asp;
	DIR				*dip;
	struct dirent	*dit;

	if ((dip = opendir(bin)) != NULL)
	{
		while ((dit = readdir(dip)) != NULL)
		{
			asp = NULL;
			ft_asprintf(&asp, "%s/%s", bin, dit->d_name);
			if (asp)
			{
				if (dit->d_name[0] != '.')
				{
					if (!ft_hmap_insert(&(reg->bin_hashmap), dit->d_name, asp))
						free(asp);
				}
				else
					free(asp);
			}
		}
		if (!closedir(dip))
			return ;
	}
}

static void	hash_builtin(t_registry *reg)
{
//	ft_dprintf(2, "[ERROR] Hmap insert failure : echo built-in\n");
	if (!ft_hmap_insert(&(reg->blt_hashmap), "echo", exit_blt))
			;
	if (!ft_hmap_insert(&(reg->blt_hashmap), "cd", exit_blt))
			;
	if (!ft_hmap_insert(&(reg->blt_hashmap), "setenv", exit_blt))
			;
	if (!ft_hmap_insert(&(reg->blt_hashmap), "unsetenv", exit_blt))
			;
	if (!ft_hmap_insert(&(reg->blt_hashmap), "env", exit_blt))
			;
	if (!ft_hmap_insert(&(reg->blt_hashmap), "hash", hash_blt))
			;
	if (!ft_hmap_insert(&(reg->blt_hashmap), "exit", exit_blt))
			;
}

int			hash_blt(t_registry *reg, __unused char **av)
{
	int				i;
	char			**tabs;

	if (reg->bin_hashmap.used > 0)
		ft_hmap_free_content(&(reg->bin_hashmap), free);
	if (get_data(&(reg->env), "PATH") != NULL)
	{
		tabs = ft_strsplit(get_data(&(reg->env), "PATH"), ":");
		if (!tabs)
		return (0);
		i = 0;
		while (tabs[i])
			hash_bin(reg, tabs[i++]);
		ft_freetab(&tabs);
	}
	hash_builtin(reg);
	if (reg->blt_hashmap.used == 0)
		ft_dprintf(2, "Hashmap blt is empty.\n");
	return (1);
}

/*
** builtin = (t_builtin)ft_hmap_getdata(&(reg->blt_hashmap), "hash");
** if (builtin)
** 	if (!builtin(reg))
** 		return (0);
*/
